#include "museo.h"

GLfloat Museo::museumBlanco[] = {1.0,1.0,1.0,1.0};
GLfloat Museo::museumEmission[] = {1.0,1.0,1.0,0.0};
GLfloat Museo::museumNegro[] = {0.0,0.0,0.0,1.0};
 GLuint museumTextures[NUMTEXTURES];

Museo::Museo()
{

    initTextureMuseum();
}

Museo::~Museo()
{
clearSharedMemMuseum();
}
void Museo::initTextureMuseum()
{
	int w, h, w1, h1, w2, h2, w3, h3, w4,h4;
    museumTextures[0] = loadTexture("../textures/marble_floor.png", w,h);
    museumTextures[1] = loadTexture("../textures/red.png", w1,h1);
    museumTextures[2] = loadTexture("../textures/ceil9.png", w2,h2);
    museumTextures[3] = loadTexture("../textures/wood.png", w3,h3);
    museumTextures[4] = loadTexture("../textures/bump_green.png", w4,h4); //mapa de normales
}

void Museo::drawMuseum()
{
    glEnable(GL_TEXTURE_2D);
    GLfloat v1p[] = {0,0,0};
    GLfloat v2p[] = {72,0,0};
    GLfloat v3p[] = {72,0,64};
    GLfloat v4p[] = {0,0,64};
    GLfloat v5p[] = {4,0,4};
    GLfloat v6p[] = {12,0,4};
    GLfloat v7p[] = {12,0,0.01};
    GLfloat v8p[] = {20,0,0.01};
    GLfloat v9p[] = {20,0,4};
    GLfloat v10p[] = {52,0,4};
    GLfloat v11p[] = {52,0,0.01};
    GLfloat v12p[] = {60,0,0.01};
    GLfloat v13p[] = {60,0,4};
    GLfloat v14p[] = {68,0,4};
    GLfloat v15p[] = {68,0,28};
    GLfloat v16p[] = {71.99,0,28};
    GLfloat v17p[] = {71.99,0,36};
    GLfloat v18p[] = {68,0,36};
    GLfloat v19p[] = {68,0,60};
    GLfloat v20p[] = {40,0,60};
    GLfloat v21p[] = {40,0,63.99};
    GLfloat v22p[] = {32,0,63.99};
    GLfloat v23p[] = {32,0,60};
    GLfloat v24p[] = {4,0,60};
    GLfloat v25p[] = {4,0,36};
    GLfloat v26p[] = {0.01,0,36};
    GLfloat v27p[] = {0.01,0,28};
    GLfloat v28p[] = {4,0,28};
    GLfloat v29p[] = {16,0,16};
    GLfloat v30p[] = {32,0,16};
    GLfloat v31p[] = {32,0,19.99};
    GLfloat v32p[] = {40,0,19.99};
    GLfloat v33p[] = {40,0,16};
    GLfloat v34p[] = {56,0,16};
    GLfloat v35p[] = {56,0,28};
    GLfloat v36p[] = {52.01,0,28};
    GLfloat v37p[] = {52.01,0,36};
    GLfloat v38p[] = {56,0,36};
    GLfloat v39p[] = {56,0,48};
    GLfloat v40p[] = {40,0,48};
    GLfloat v41p[] = {40,0,44};
    GLfloat v42p[] = {52,0,44};
    GLfloat v43p[] = {52,0,20};
    GLfloat v44p[] = {48,0,20};
    GLfloat v45p[] = {48,0,16.01};
    GLfloat v46p[] = {40.01,0,16.01};
    GLfloat v47p[] = {40.01,0,20};
    GLfloat v48p[] = {31.99,0,20};
    GLfloat v49p[] = {31.99,0,15.99};
    GLfloat v50p[] = {24,0,16.01};
    GLfloat v51p[] = {24,0,20};
    GLfloat v52p[] = {20,0,20};
    GLfloat v53p[] = {20,0,44};
    GLfloat v54p[] = {32,0,44};
    GLfloat v55p[] = {32,0,48};
    GLfloat v56p[] = {16,0,48};
    GLfloat v57p[] = {16,0,36};
    GLfloat v58p[] = {19.99,0,36};
    GLfloat v59p[] = {19.99,0,28};
    GLfloat v60p[] = {16,0,28};

    //vertices techo
    GLfloat v1t[] = {0,16,0};
    GLfloat v2t[] = {72,16,0};
    GLfloat v3t[] = {72,16,64};
    GLfloat v4t[] = {0,16,64};
    GLfloat v5t[] = {4,16,4};
    GLfloat v6t[] = {12,16,4};
    GLfloat v7t[] = {12,16,0.01};
    GLfloat v8t[] = {20,16,0.01};
    GLfloat v9t[] = {20,16,4};
    GLfloat v10t[] = {52,16,4};
    GLfloat v11t[] = {52,16,0.01};
    GLfloat v12t[] = {60,16,0.01};
    GLfloat v13t[] = {60,16,4};
    GLfloat v14t[] = {68,16,4};
    GLfloat v15t[] = {68,16,28};
    GLfloat v16t[] = {71.99,16,28};
    GLfloat v17t[] = {71.99,16,36};
    GLfloat v18t[] = {68,16,36};
    GLfloat v19t[] = {68,16,60};
    GLfloat v20t[] = {40,16,60};
    GLfloat v21t[] = {40,16,63.99};
    GLfloat v22t[] = {32,16,63.99};
    GLfloat v23t[] = {32,16,60};
    GLfloat v24t[] = {4,16,60};
    GLfloat v25t[] = {4,16,36};
    GLfloat v26t[] = {0.01,16,36};
    GLfloat v27t[] = {0.01,16,28};
    GLfloat v28t[] = {4,16,28};
    GLfloat v29t[] = {16,16,16};
    GLfloat v30t[] = {32,16,16};
    GLfloat v31t[] = {32,16,19.99};
    GLfloat v32t[] = {40,16,19.99};
    GLfloat v33t[] = {40,16,16};
    GLfloat v34t[] = {56,16,16};
    GLfloat v35t[] = {56,16,28};
    GLfloat v36t[] = {52.01,16,28};
    GLfloat v37t[] = {52.01,16,36};
    GLfloat v38t[] = {56,16,36};
    GLfloat v39t[] = {56,16,48};
    GLfloat v40t[] = {40,16,48};
    GLfloat v41t[] = {40,16,44};
    GLfloat v42t[] = {52,16,44};
    GLfloat v43t[] = {52,16,20};
    GLfloat v44t[] = {48,16,20};
    GLfloat v45t[] = {48,16,16.01};
    GLfloat v46t[] = {40.01,16,16.01};
    GLfloat v47t[] = {40.01,16,20};
    GLfloat v48t[] = {31.99,16,20};
    GLfloat v49t[] = {31.99,16,15.99};
    GLfloat v50t[] = {24,16,16.01};
    GLfloat v51t[] = {24,16,20};
    GLfloat v52t[] = {20,16,20};
    GLfloat v53t[] = {20,16,44};
    GLfloat v54t[] = {32,16,44};
    GLfloat v55t[] = {32,16,48};
    GLfloat v56t[] = {16,16,48};
    GLfloat v57t[] = {16,16,36};
    GLfloat v58t[] = {19.99,16,36};
    GLfloat v59t[] = {19.99,16,28};
    GLfloat v60t[] = {16,16,28};


  glBindTexture(GL_TEXTURE_2D, museumTextures[0]);
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //---1
  setTheMaterial(museumNegro,museumBlanco,museumBlanco,museumNegro);
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(5.0,0.0); glVertex3fv(v3p);
  glTexCoord2f(5.0,5.0); glVertex3fv(v2p);
  glTexCoord2f(0.0,5.0); glVertex3fv(v1p);
  glTexCoord2f(0.0,0.0); glVertex3fv(v4p);
  glEnd();     
  glPopAttrib(); 
   
  //Techo
  glBindTexture(GL_TEXTURE_2D, museumTextures[2]);
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//--2
  setTheMaterial(museumNegro,museumBlanco,museumBlanco,museumNegro);
  glColor3f(1.0,1.0,1.0);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v1t);
  glTexCoord2f(9.0,0.0); glVertex3fv(v2t);
  glTexCoord2f(9.0,8.0); glVertex3fv(v3t);
  glTexCoord2f(0.0,8.0); glVertex3fv(v4t);
  glEnd();
  glPopAttrib();
    
  //PAREDES EXTERNAS EXTERIORES
  glBindTexture(GL_TEXTURE_2D, museumTextures[1]);
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setTheMaterial(museumNegro,museumBlanco,museumBlanco,museumNegro);
  glColor3f(1.0,1.0,1.0);
  
  //Trasera
  glNormal3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0,1.0); glVertex3fv(v2t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v1t);
  glTexCoord2f(0.0,0.0); glVertex3fv(v1p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v2p);
  glEnd();     

  //Delantera
  glNormal3f(0.0f, 0.0f, -1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,1.0); glVertex3fv(v3t);
  glTexCoord2f(0.0,0.0); glVertex3fv(v3p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v4p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v4t); 
  glEnd();

  //Derecha
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0,1.0); glVertex3fv(v3t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v2t);
  glTexCoord2f(0.0,0.0); glVertex3fv(v2p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v3p);
  glEnd();

  //Izquierda
  glNormal3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v4p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v1p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v1t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v4t);
  glEnd();
  //FIN PAREDES EXTERNAS EXTERIORES
  
  //PAREDES EXTERNAS CARA INTERIOR  
  //Traseras
  glNormal3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v5p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v6p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v6t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v5t);
  glEnd();  
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v7p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v8p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v8t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v7t);
  glEnd();   
  
  glNormal3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v9p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v10p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v10t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v9t);
  glEnd();  
     
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v11p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v12p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v12t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v11t);
  glEnd();        

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v13p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v14p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v14t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v13t);
  glEnd();  
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v15p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v16p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v16t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v15t);
  glEnd();        

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v27p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v28p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v28t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v27t);
  glEnd();    
  
  // -----Pabellon------//
  glNormal3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v36p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v35p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v35t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v36t);
  glEnd();  
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v40p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v39p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v39t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v40t);
  glEnd();   
  
  glNormal3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v44p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v43p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v43t);
  glTexCoord2f(0.0,1.0); glVertex3fv(v44t);
  glEnd();  
     
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v46p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v45p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v45t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v46t);
  glEnd();        

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v48p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v47p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v47t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v48t);
  glEnd();  
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v50p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v49p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v49t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v50t);
  glEnd();        

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v52p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v51p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v51t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v52t);
  glEnd();  
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v56p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v55p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v55t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v56t);
  glEnd();        

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v60p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v59p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v59t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v60t);
  glEnd();        
 
  //Delanteras
  glNormal3f(0.0f, 0.0f, -1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v17p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v18p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v18t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v17t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v19p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v20p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v20t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v19t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v21p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v22p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v22t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v21t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v23p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v24p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v24t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v23t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v25p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v26p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v26t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v25t);
  glEnd();   
  
  // -----Pabellon------//
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v30p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v29p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v29t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v30t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v47p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v48p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v48t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v47t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v34p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v33p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v33t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v34t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v38p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v37p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v37t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v38t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v42p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v41p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v41t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v42t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v54p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v53p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v53t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v54t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v58p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v57p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v57t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v58t);
  glEnd();  
       
  //Derechas
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v8p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v9p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v9t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v8t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v12p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v13p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v13t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v12t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v14p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v15p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v15t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v14t);
  glEnd();    
  
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v16p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v17p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v17t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v16t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v18p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v19p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v19t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v18t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v20p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v21p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v21t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v20t);
  glEnd();  
  
  // -----Pabellon------//
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v33p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v32p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v32t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v33t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v41p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v40p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v40t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v41t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v43p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v42p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v42t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v43t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v45p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v44p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v44t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v45t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v49p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v48p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v48t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v49t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v57p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v56p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v56t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v57t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v59p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v58p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v58t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v59t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v29p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v60p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v60t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v29t);
  glEnd();     

  //Izquierdas
  glNormal3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v6p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v7p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v7t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v6t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v10p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v11p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v11t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v10t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v22p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v23p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v23t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v22t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v24p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v25p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v25t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v24t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v26p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v27p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v27t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v26t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v28p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v5p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v5t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v28t);
  glEnd();
  
  // -----Pabellon------//
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v31p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v30p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v30t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v31t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v35p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v34p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v34t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v35t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v37p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v36p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v36t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v37t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v39p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v38p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v38t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v39t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v47p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v46p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v46t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v47t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v51p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v50p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v50t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v51t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v53p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v52p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v52t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v53t);
  glEnd();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3fv(v55p);
  glTexCoord2f(1.0,0.0); glVertex3fv(v54p);
  glTexCoord2f(1.0,1.0); glVertex3fv(v54t);  
  glTexCoord2f(0.0,1.0); glVertex3fv(v55t);
  glEnd();    
    
  //FIN PAREDES EXTERNAS CARA INTERIOR  
  
  glPopAttrib();	
  glDisable(GL_TEXTURE_2D);
}

void Museo::clearSharedMemMuseum()
{
	
    //glDeleteTextures(1, &texture4Render);
    //texture4Render = 0;
   glDeleteTextures(NUMTEXTURES, museumTextures);
    for(int i = 0; i < NUMTEXTURES; i++)
	{
        museumTextures[i] = 0;
	}

   /*glDeleteFramebuffers(1, &fboID);
    fboID = 0;
    glDeleteRenderbuffers(1, &rboID);
    rboID = 0;*/
}

void Museo::setTheMaterial( const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular,const GLfloat *emission)
{
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_EMISSION, emission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 35.0);
}
