#include "xcmodel.h"
#include <cmath>
#include <fstream>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;

GLuint xcModel::modelcount = 0;
/*GLuint xcModel::indexVertex = 0;
GLuint xcModel::indexNormal = 1;
GLuint xcModel::indexTexture = 2;
GLuint xcModel::indexColor = 3;*/

xcModel::xcModel(string archivoMesh, string vertexShaderFile, string fragmentShaderFile)
{

 //cout << modelcount  << "Model count "<< endl;
  readModel(archivoMesh);

  createDisplayList();

  glGenBuffers(1,&vboID);
  glBindBuffer(GL_ARRAY_BUFFER,vboID);
  glBufferData(GL_ARRAY_BUFFER,sizeof(MyVertex)*vertices.size(),NULL, GL_STATIC_DRAW);
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,0, sizeof(MyVertex)*vertices.size(),&vertices[0]);
  glVertexAttribPointer(SlotPosition+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(0));
  glVertexAttribPointer(SlotNormal+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex),BUFFER_OFFSET(12) );
  glVertexAttribPointer(SlotTexCoord+(4*modelcount), 2, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(24));
  glVertexAttribPointer(SlotColor+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(32));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glGenBuffers(1, &vboIndex);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  mId = modelcount;
  shader = new GLSLProgram(vertexShaderFile,fragmentShaderFile,pID,false);
  putBindAttribLocationFor();
  projM = glGetUniformLocation(pID, "projMatrix");
  viewM = glGetUniformLocation(pID, "viewMatrix");

  modelcount++;
}

xcModel::xcModel(string archivoMesh)
{

  readModel(archivoMesh);

  createDisplayList();

  glGenBuffers(1,&vboID);
  glBindBuffer(GL_ARRAY_BUFFER,vboID);
  glBufferData(GL_ARRAY_BUFFER,sizeof(MyVertex)*vertices.size(),NULL, GL_STATIC_DRAW);
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,0, sizeof(MyVertex)*vertices.size(),&vertices[0]);
  glVertexAttribPointer(SlotPosition+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(0));
  glVertexAttribPointer(SlotNormal+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex),BUFFER_OFFSET(12) );
  glVertexAttribPointer(SlotTexCoord+(4*modelcount), 2, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(24));
  glVertexAttribPointer(SlotColor+(4*modelcount), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(32));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glGenBuffers(1, &vboIndex);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    mId = modelcount;
  modelcount++;
}



xcModel::~xcModel()
{
 
  glDeleteBuffers(1,&vboID);
  glDeleteBuffers(1,&vboIndex);
  delete shader;
  glDeleteLists(displayList,1);
}

void xcModel::setShader(string vertexShaderFile, string fragmentShaderFile)
{
  shader = new GLSLProgram(vertexShaderFile,fragmentShaderFile,pID,false);
}

void xcModel::paintModelVBO()
{

  glBindBuffer(GL_ARRAY_BUFFER_ARB, vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
  glEnableVertexAttribArray(SlotPosition+(4*mId));
  glEnableVertexAttribArray(SlotNormal+(4*mId));
  glEnableVertexAttribArray(SlotTexCoord+(4*mId));
  glEnableVertexAttribArray(SlotColor+(4*mId));
  // glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  //glTexCoordPointer(2, GL_FLOAT, sizeof(MyVertex), BUFFER_OFFSET(24));

  glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  
  //glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
  glDisableVertexAttribArray(SlotPosition+(4*mId));
  glDisableVertexAttribArray(SlotNormal+(4*mId));
  glDisableVertexAttribArray(SlotTexCoord+(4*mId));
  glDisableVertexAttribArray(SlotColor+(4*mId));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER_ARB, 0);

}

void xcModel::paintModelWithShader()
{

	shader->useShaders(pID);
	
	paintModelVBO();
	
	shader->useShaders(0);


}

void xcModel::activeShader()
{
    shader->useShaders(pID);
}

void xcModel::disactiveShader()
{
    shader->useShaders(0);
}


void xcModel::readModel(string readModel)
{

  readPLY(readModel);
  for(unsigned int i = 0; i < indices.size(); i = i+3)
    {
      calculateNormals(&vertices[indices[i]],
		       &vertices[indices[i+1]],
		       &vertices[indices[i+2]]);
    }

}

void xcModel::calculateNormals(MyVertex *v1, MyVertex *v2, MyVertex *v3)
{
 
  float normal[3];
  float x1 = v2->x - v1->x;
  float y1 = v2->y - v1->y;
  float z1 = v2->z - v1->z;

  float x2 = v3->x - v1->x;
  float y2 = v3->y - v1->y;
  float z2 = v3->z - v1->z;

  normal[0] = y1*z2 - z1*y2;
  normal[1] = z1*x2 - x1*z2;
  normal[2] = x1*y2 - y1*x2;
  
  float norm = sqrt( normal[0]* normal[0] + 
		     normal[1]* normal[1] + 
		     normal[2]* normal[2]);



  v1->nx = normal[0]/norm;
  v1->ny = normal[1]/norm;
  v1->nz = normal[2]/norm;

  v2->nx = normal[0]/norm;
  v2->ny = normal[1]/norm;
  v2->nz = normal[2]/norm;

  v3->nx = normal[0]/norm;
  v3->ny = normal[1]/norm;
  v3->nz = normal[2]/norm;



  v1->r = normal[0]/norm;
  v1->g = normal[1]/norm;
  v1->b = normal[2]/norm;

  v2->r = normal[0]/norm;
  v2->g = normal[1]/norm;
  v2->b = normal[2]/norm;

  v3->r = normal[0]/norm;
  v3->g = normal[1]/norm;
  v3->b = normal[2]/norm;


}

/*LLena los arreglos de vertices e índices*/
void xcModel::readPLY(string nombreArchivo)
{
  ifstream myfile(nombreArchivo.c_str());
  string a;
  bool propON = false, propFace = false;
  int numVertices, numFaces, numProp = 0, numPropF = 0;
  if(!myfile.is_open())
    {
      cout << "No se encontró el archivo" << endl;
      return;
    } 
  else 
    {
	
      while(myfile.good() && a.compare("end_header") != 0)
	{
	  myfile >> a;
	  if(!a.compare("vertex")){
	    propON = true;
	    myfile >> numVertices;
	  }
	  if(!a.compare("face")){
	    propON = false;
	    propFace = true;
	    myfile >> numFaces;
	  }
	  if(!a.compare("property"))
	    {
	      if(propON)
		numProp++;
	      if(propFace)
		numPropF++;
	    }
	      
	}
    }
  cout << numProp << endl;
  cout << numPropF << endl;
  int cont = 0;
  do{
    MyVertex v;
    
    myfile >> v.x >> v.y >> v.z;
    vertices.push_back(v);
    
    int dif = numProp - 3;
    if(dif > 0)
      for(int d = 0; d < dif; d++)
	myfile >> a;
      
    
    cont++;
  }
  while(myfile.good() && cont < numVertices);

  int num = 0, f = 0;
  do {
  
    int ind;
    myfile >> ind;
    if(num % 4 != 0)
      {
	indices.push_back(ind);
	f++;
      }
    num++;
    
  }while(myfile.good());
   
  myfile.close();
  


  cout << "vertices " << vertices.size() << " arreglo, " << numVertices << " archivo " <<  endl;
  cout << "indices " << indices.size()/3 << " arreglo, " << numFaces << " archivo" <<  endl;
  cout << "arreglo de vértices y de índices lleno" << endl;
}

bool xcModel::putBindAttribLocationFor()
{


    cout << "Binding Attributes" << endl;
  shader->bindAttributeLocation(pID,SlotPosition+(4*mId),"in_Position");
  shader->bindAttributeLocation(pID,SlotNormal+(4*mId),"in_Normal");
  shader->bindAttributeLocation(pID,SlotTexCoord+(4*mId),"in_TexCoord");
  shader->bindAttributeLocation(pID,SlotColor+(4*mId),"in_Color");
  shader->bindFragDataLocation(pID);
  shader->linkProgram(pID);

  return true;
}

void xcModel::createDisplayList()
{

    float v1x,v1y,v1z;
     float v2x,v2y,v2z;
     float v3x,v3y,v3z;
     displayList = glGenLists(1);
     glNewList(displayList,GL_COMPILE);
     glBegin(GL_TRIANGLES);
     glEnable(GL_NORMALIZE);
     for(unsigned int i = 0; i < indices.size(); i = i + 3)
       {

         v1x = vertices[indices[i]].x;
         v1y = vertices[indices[i]].y;
         v1z = vertices[indices[i]].z;


         v2x = vertices[indices[i+1]].x;
         v2y = vertices[indices[i+1]].y;
         v2z = vertices[indices[i+1]].z;

         v3x = vertices[indices[i+2]].x;
         v3y = vertices[indices[i+2]].y;
         v3z = vertices[indices[i+2]].z;



         float *n;
         n = calculateNormals(v1x, v1y, v1z, v2x, v2y, v2z,v3x, v3y, v3z);

         glNormal3fv(n);
         glVertex3f(v1x,v1y,v1z);
         glVertex3f(v2x,v2y,v2z);
         glVertex3f(v3x,v3y,v3z);

       }
     glEnd();
     glEndList();

}

float* xcModel::calculateNormals(float v1x, float v1y, float v1z,
                 float v2x, float v2y, float v2z,
                 float v3x, float v3y, float v3z)
{

  float normal[3];
  float x1 = v2x - v1x;
  float y1 = v2y - v1y;
  float z1 = v2z - v1z;

  float x2 = v3x - v1x;
  float y2 = v3y - v1y;
  float z2 = v3z - v1z;

  normal[0] = y1*z2 - z1*y2;
  normal[1] = -(x1*z2 - z1*x2);
  normal[2] = x1*y2 - y1*x2;

  float norm = sqrt( normal[0]* normal[0] +
             normal[1]* normal[1] +
             normal[2]* normal[2]);

  normal[0] = normal[0]/norm;
  normal[1] = normal[1]/norm;
  normal[2] = normal[2]/norm;

  return normal;
}

void xcModel::paintDisplayList()
{
    glCallList(displayList);
}

void xcModel::setMVPM(float p[], float v[])
{

    shader->setUniformMatrix4(pID,p,"projMatrix",projM);
    shader->setUniformMatrix4(pID,v,"viewMatrix",viewM);
}

void xcModel::setTime(float timef)
{
    shader->setUniform1f(pID,tLoc,"time",timef);

}
