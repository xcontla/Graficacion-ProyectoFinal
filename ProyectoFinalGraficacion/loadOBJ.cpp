#include "loadOBJ.h"

LoadOBJ::LoadOBJ(const char *filename, GLuint m)
{


  xlow = xhigh = ylow = yhigh =  zlow = zhigh = 0.0;
  vboId = 0; 
  vboIndex = 0;

  numIndices = 0;
  numVertices = 0;
  mid = m;
  std::cout << "initializar" << std::endl;

  if(!ReadOBJModel(filename))
    exit(1);
  std::cout << "initializado" << std::endl;
  passToVBO();
}


void LoadOBJ::FreeModel (){
  int i;
	
		if (&mdl)
    	{
			if (mdl.vertices)
			{
				free (mdl.vertices);
				mdl.vertices = NULL;
			}
		
			if (mdl.texCoords)
			{
				free (mdl.texCoords);
				mdl.texCoords = NULL;
			}
		
			if (mdl.normals)
			{
				free (mdl.normals);
				mdl.normals = NULL;
			}
		
			if (mdl.faces)
			{
				for (i = 0; i < mdl.num_faces; ++i)
				{
					if (mdl.faces[i].vert_indices)
						free (mdl.faces[i].vert_indices);
				
					if (mdl.faces[i].uvw_indices)
						free (mdl.faces[i].uvw_indices);
				
					if (mdl.faces[i].norm_indices)
						free (mdl.faces[i].norm_indices);
				}
			
			free (mdl.faces);
			mdl.faces = NULL;
			}
		}

        delete shader;

}

/**
 * Allocate resources for the model after first pass.
 */
int  LoadOBJ::MallocModel(){
		if (mdl.num_verts)
    	{
			mdl.vertices = (struct obj_vertex_t *)
				malloc (sizeof (struct obj_vertex_t) * mdl.num_verts);
			if (!mdl.vertices)
				return 0;
    		}
	
			if (mdl.num_texCoords)
    		{
				mdl.texCoords = (struct obj_texCoord_t *)
					malloc (sizeof (struct obj_texCoord_t) * mdl.num_texCoords);
				if (!mdl.texCoords)
					return 0;
    }
	
	if (mdl.num_normals)
    {
		mdl.normals = (struct obj_normal_t *)
		malloc (sizeof (struct obj_normal_t) * mdl.num_normals);
		if (!mdl.normals)
			return 0;
    }
	
	if (mdl.num_faces)
    {
		mdl.faces = (struct obj_face_t *)
		calloc (mdl.num_faces, sizeof (struct obj_face_t));
		if (!mdl.faces)
			return 0;
    }
	
	return 1;
}

/**
 * Load an OBJ model from file -- first pass.
 * Get the number of triangles/vertices/texture coords for
 * allocating buffers.
 */
int  LoadOBJ::FirstPass (FILE *fp)
{
	int v, t, n;
	char buf[256];
	
	while (!feof (fp))
    {
		/* Read whole line */
		fgets (buf, sizeof (buf), fp);
		
		switch (buf[0])
		{
			case 'v':
			{
				if (buf[1] == ' ')
				{
					/* Vertex */
					mdl.num_verts++;
				}
				else if (buf[1] == 't')
				{
					/* Texture coords. */
					mdl.num_texCoords++;
				}
				else if (buf[1] == 'n')
				{
					/* Normal vector */
					mdl.num_normals++;
				}
				else
				{
					printf ("Warning: unknown token \"%s\"! (ignoring)\n", buf);
				}
				
				break;
			}
				
			case 'f':
			{
				/* Face */
				if (sscanf (buf + 2, "%d/%d/%d", &v, &n, &t) == 3)
				{
					mdl.num_faces++;
					mdl.has_texCoords = 1;
					mdl.has_normals = 1;
				}
				else if (sscanf (buf + 2, "%d//%d", &v, &n) == 2)
				{
					mdl.num_faces++;
					mdl.has_texCoords = 0;
					mdl.has_normals = 1;
				}
				else if (sscanf (buf + 2, "%d/%d", &v, &t) == 2)
				{
					mdl.num_faces++;
					mdl.has_texCoords = 1;
					mdl.has_normals = 0;
				}
				else if (sscanf (buf + 2, "%d", &v) == 1)
				{
					mdl.num_faces++;
					mdl.has_texCoords = 0;
					mdl.has_normals = 0;
				}
				else
				{
					/* Should never be there or the model is very crappy */
					fprintf (stderr, "Error: found face with no vertex!\n");
				}
				
				break;
			}
				
			case 'g':
			{
				/* Group */
				/*	fscanf (fp, "%s", buf); */
				break;
			}
				
			default:
				break;
		}
    }
	
	/* Check if informations are valid */
	if ((mdl.has_texCoords && !mdl.num_texCoords) ||
		(mdl.has_normals && !mdl.num_normals))
    {
		fprintf (stderr, "error: contradiction between collected info!\n");
		return 0;
    }
	
	if (!mdl.num_verts)
    {
		fprintf (stderr, "error: no vertex found!\n");
		return 0;
    }
	
	printf ("first pass results: found\n");
	printf ("   * %i vertices\n", mdl.num_verts);
	printf ("   * %i texture coords.\n", mdl.num_texCoords);
	printf ("   * %i normal vectors\n", mdl.num_normals);
	printf ("   * %i faces\n", mdl.num_faces);
	printf ("   * has texture coords.: %s\n", mdl.has_texCoords ? "yes" : "no");
	printf ("   * has normals: %s\n", mdl.has_normals ? "yes" : "no");
	
	return 1;
}

/**
 * Load an OBJ model from file -- first pass.
 * This time, read model data and feed buffers.
 */
int  LoadOBJ::SecondPass (FILE *fp)
{
	struct obj_vertex_t *pvert = mdl.vertices;
	struct obj_texCoord_t *puvw = mdl.texCoords;
	struct obj_normal_t *pnorm = mdl.normals;
	struct obj_face_t *pface = mdl.faces;
	char buf[128], *pbuf;
	int i;
	xlow = 10000.0;
	xhigh = -1000.0;
	zlow = 10000.0;
	zhigh = -1000.0;
	ylow = 10000.0;
	yhigh = -1000.0;

	while (!feof (fp))
    {
		/* Read whole line */
		fgets (buf, sizeof (buf), fp);
		
		switch (buf[0])
		{
			case 'v':
			{
				if (buf[1] == ' ')
				{
					/* Vertex */
					if (sscanf (buf + 2, "%f %f %f %f",
								&pvert->xyzw[0], &pvert->xyzw[1],
								&pvert->xyzw[2], &pvert->xyzw[3]) != 4)
					{
						if (sscanf (buf + 2, "%f %f %f", &pvert->xyzw[0],
									&pvert->xyzw[1], &pvert->xyzw[2] ) != 3)
						{
							fprintf (stderr, "Error reading vertex data!\n");
							return 0;
						}
						else
						{
							pvert->xyzw[3] = 1.0;
						}
					}
					
				
					if(xlow > pvert->xyzw[0])
					  xlow = pvert->xyzw[0];
					if(xhigh < pvert->xyzw[0])
					  xhigh = pvert->xyzw[0];
					if(zlow > pvert->xyzw[2])
					  zlow = pvert->xyzw[2];
					if(zhigh < pvert->xyzw[2])
					  zhigh = pvert->xyzw[2];
					if(ylow > pvert->xyzw[1])
					  ylow = pvert->xyzw[1];
					if(yhigh < pvert->xyzw[1])
					yhigh = pvert->xyzw[1];


					pvert++;
				}
				else if (buf[1] == 't')
				{
					/* Texture coords. */
					if (sscanf (buf + 2, "%f %f %f", &puvw->uvw[0],
								&puvw->uvw[1], &puvw->uvw[2]) != 3)
					{
						if (sscanf (buf + 2, "%f %f", &puvw->uvw[0],
									&puvw->uvw[1]) != 2)
						{
							if (sscanf (buf + 2, "%f", &puvw->uvw[0]) != 1)
							{
								fprintf (stderr, "Error reading texture coordinates!\n");
								return 0;
							}
							else
							{
								puvw->uvw[1] = 0.0;
								puvw->uvw[2] = 0.0;
							}
						}
						else
						{
							puvw->uvw[2] = 0.0;
						}
					}
					
					puvw++;
				}
				else if (buf[1] == 'n')
				{
					/* Normal vector */
					if (sscanf (buf + 2, "%f %f %f", &pnorm->ijk[0],
								&pnorm->ijk[1], &pnorm->ijk[2]) != 3)
					{
						fprintf (stderr, "Error reading normal vectors!\n");
						return 0;
					}
					
					pnorm++;
				}
				
				break;
			}
				
			case 'f':
			{
				pbuf = buf;
				pface->num_elems = 0;
				
				/* Count number of vertices for this face */
				while (*pbuf)
				{
					if (*pbuf == ' ')
						pface->num_elems++;
					
					pbuf++;
				}
				
				/* Select primitive type */
				if (pface->num_elems < 3)
				{
					fprintf (stderr, "Error: a face must have at least 3 vertices!\n");
					return 0;
				}
				else if (pface->num_elems == 3)
				{
					pface->type = GL_TRIANGLES;
				}
				else if (pface->num_elems == 4)
				{
					pface->type = GL_QUADS;
				}
				else
				{
					pface->type = GL_POLYGON;
				}
				
				/* Memory allocation for vertices */
				pface->vert_indices = (int *)malloc (sizeof (int) * pface->num_elems);
				
				if (mdl.has_texCoords)
					pface->uvw_indices = (int *)malloc (sizeof (int) * pface->num_elems);
				
				if (mdl.has_normals)
					pface->norm_indices = (int *)malloc (sizeof (int) * pface->num_elems);
				
				/* Read face data */
				pbuf = buf;
				i = 0;
				
				for (i = 0; i < pface->num_elems; ++i)
				{
					pbuf = strchr (pbuf, ' ');
					pbuf++; /* Skip space */
					
					/* Try reading vertices */
					if (sscanf (pbuf, "%d/%d/%d",
								&pface->vert_indices[i],
								&pface->uvw_indices[i],
								&pface->norm_indices[i]) != 3)
					{
						if (sscanf (pbuf, "%d//%d", &pface->vert_indices[i],
									&pface->norm_indices[i]) != 2)
						{
							if (sscanf (pbuf, "%d/%d", &pface->vert_indices[i],
										&pface->uvw_indices[i]) != 2)
							{
								sscanf (pbuf, "%d", &pface->vert_indices[i]);
							}
						}
					}
					
					/* Indices must start at 0 */
					pface->vert_indices[i]--;
					
					if (mdl.has_texCoords)
						pface->uvw_indices[i]--;
					
					if (mdl.has_normals)
						pface->norm_indices[i]--;
				}
				
				pface++;
				break;
			}
		}
    }
	
	printf ("second pass results: read\n");
	printf ("   * %i vertices\n",pvert - mdl.vertices);
	printf ("   * %i texture coords.\n", puvw - mdl.texCoords);
	printf ("   * %i normal vectors\n", pnorm - mdl.normals);
	printf ("   * %i faces\n", pface - mdl.faces);
	
	return 1;
}

/**
 * Load an OBJ model from file, in two passes.
 */
int  LoadOBJ::ReadOBJModel (const char *filename)
{
	FILE *fp;
	
	fp = fopen (filename, "r");
	if (!fp)
    {
		fprintf (stderr, "Error: couldn't open \"%s\"!\n", filename);
		return 0;
    }
    //std::cout << "premem" << std::endl;
	/* reset model data */
	memset (&mdl, 0, sizeof (struct obj_model_t));
    //std::cout << "memorioainitializado" << std::endl;
	/* first pass: read model info */
	if (!FirstPass (fp))
    {
		fclose (fp);
		return 0;
    }
	
	rewind (fp);
	
	/* memory allocation */
	if (!MallocModel ())
    {
		fclose (fp);
		FreeModel ();
		return 0;
    }
	
	/* second pass: read model data */
	if (!SecondPass (fp))
    {
		fclose (fp);
		FreeModel ();
		return 0;
    }
	
	fclose (fp);
	return 1;
}

/**
 * Draw the OBJ model.
 */
void  LoadOBJ::RenderOBJModel ()
{
        int i, j;
        
        for (i = 0; i < mdl.num_faces; ++i)
    {
      glBegin (mdl.faces[i].type);
      //glBegin (GL_LINE_STRIP);
                for (j = 0; j < mdl.faces[i].num_elems; ++j)
                {
                        if (mdl.has_texCoords)
                                glTexCoord3fv (mdl.texCoords[mdl.faces[i].uvw_indices[j]].uvw);
                        
                        if (mdl.has_normals)
                                glNormal3fv (mdl.normals[mdl.faces[i].norm_indices[j]].ijk);
                        
                        glVertex4fv (mdl.vertices [mdl.faces[i].vert_indices[j]].xyzw);
                }
                glEnd();
    }
}



void  LoadOBJ::passToVBO()
{
  int i, j;
  MyVertex m;
  
  float dx = (xlow - xhigh) * (xlow - xhigh) ;
  dx = sqrt(dx);

  float dz = (zlow - zhigh) * (zlow - zhigh) ;
  dz = sqrt(dz);



  for (i = 0; i < mdl.num_faces; ++i)
    {
      for (j = 0; j < mdl.faces[i].num_elems; ++j)
	{
	  /*	  if (mdl->has_texCoords)
	    glTexCoord3fv (mdl->texCoords[mdl->faces[i].uvw_indices[j]].uvw);
                        
	  if (mdl->has_normals)
	  glNormal3fv (mdl->normals[mdl->faces[i].norm_indices[j]].ijk);*/
                        
	  // glVertex4fv (mdl->vertices [mdl->faces[i].vert_indices[j]].xyzw);
	  m.x = mdl.vertices [mdl.faces[i].vert_indices[j]].xyzw[0];
	  m.y = mdl.vertices [mdl.faces[i].vert_indices[j]].xyzw[1];
	  m.z = mdl.vertices [mdl.faces[i].vert_indices[j]].xyzw[2];

	  m.nx = 0.0;
	  m.ny = 1.0;
	  m.nz = 0.0;

	  m.s0 = m.x/dx;
	  m.t0 = m.z/dz;
      
	  m.r = m.s0;
	  m.g = (m.t0+m.s0)/2.0;
	  m.b = m.t0;

	  vboS.push_back(m);
	  numVertices++;
	}
         
    }

 for (i = 0; i < mdl.num_faces; ++i)
    {
      for (j = 0; j < mdl.faces[i].num_elems; ++j)
	{
     // std::cout <<  numIndices << std::endl;
	  m_indices.push_back(numIndices);
	  numIndices++;
	  
	}
         
    }


}

void LoadOBJ::initVBO()
{

  
  glGenBuffersARB(1, &vboId);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(MyVertex)*numVertices, NULL, GL_DYNAMIC_DRAW);
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB,0, sizeof(MyVertex)*numVertices,&vboS[0]);
  glVertexAttribPointer(SlotPosition+(4*mid), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(0));
  glVertexAttribPointer(SlotNormal+(4*mid), 3, GL_FLOAT, 0, sizeof(MyVertex),BUFFER_OFFSET(12) );
  glVertexAttribPointer(SlotTexCoord+(4*mid), 2, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(24));
  glVertexAttribPointer(SlotColor+(4*mid), 3, GL_FLOAT, 0, sizeof(MyVertex), BUFFER_OFFSET(32));

 
  glGenBuffers(1, &vboIndex);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*numIndices, &m_indices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void LoadOBJ::initShader(std::string vertexShaderFile, std::string fragmentShaderFile)
{

    shader = new GLSLProgram(vertexShaderFile,fragmentShaderFile,pID,false);
    putBindAttribLocationFor();
    projM = glGetUniformLocation(pID, "projMatrix");
    viewM = glGetUniformLocation(pID, "viewMatrix");

}


void  LoadOBJ::renderOBJ()
{

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
  glEnableVertexAttribArray(SlotPosition+(4*mid));
  glEnableVertexAttribArray(SlotNormal+(4*mid));
  glEnableVertexAttribArray(SlotTexCoord+(4*mid));
  glEnableVertexAttribArray(SlotColor+(4*mid));
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, sizeof(MyVertex), BUFFER_OFFSET(24));
  glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_INT,BUFFER_OFFSET(0));
  
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
  glDisableVertexAttribArray(SlotColor+(4*mid));
  glDisableVertexAttribArray(SlotTexCoord+(4*mid));
  glDisableVertexAttribArray(SlotNormal+(4*mid));
  glDisableVertexAttribArray(SlotPosition+(4*mid));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

}

bool LoadOBJ::putBindAttribLocationFor()
{


  //cout << "Binding Attributes" << endl;
  shader->bindAttributeLocation(pID,SlotPosition+(4*mid),"in_Position");
  shader->bindAttributeLocation(pID,SlotNormal+(4*mid),"in_Normal");
  shader->bindAttributeLocation(pID,SlotTexCoord+(4*mid),"in_TexCoord");
  shader->bindAttributeLocation(pID,SlotColor+(4*mid),"in_Color");
  shader->bindFragDataLocation(pID);
  shader->linkProgram(pID);

  return true;
}

void LoadOBJ::activeShader()
{
    shader->useShaders(pID);
}

void LoadOBJ::disactiveShader()
{
    shader->useShaders(0);
}

void LoadOBJ::setMVPM(float p[], float v[])
{
    shader->setUniformMatrix4(pID,p,"projMatrix",projM);
    shader->setUniformMatrix4(pID,v,"viewMatrix",viewM);
}

void LoadOBJ::setTime(float timef)
{
    shader->setUniform1f(pID,tLoc,"time",timef);

}
