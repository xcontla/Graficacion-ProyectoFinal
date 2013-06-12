#ifndef XCMODEL_H
#define XCMODEL_H

#include "xcstructures.h"
#include "glslProgram.h"
#include <vector>

class xcModel
{

 public:
		  
  xcModel(std::string archivoMesh, std::string vertexShaderFile, std::string fragmentShaderFile);
  xcModel(std::string archivoMesh);
  ~xcModel();
		  
  void setShader(std::string vertexShaderFile, std::string fragmentShaderFile);
  void paintModelVBO();
  void paintModelWithShader();
  void activeShader();
  void disactiveShader();
  void readModel(std::string archivoMesh);
  void readPLY(std::string nombreArchivo);
  void calculateNormals(MyVertex *v1, MyVertex *v2, MyVertex *v3);
  bool putBindAttribLocationFor();
  GLSLProgram* getShader(){return this->shader;}
  GLuint getProgramID(){return this->pID;}
  void createDisplayList();

  float* calculateNormals(float v1x, float v1y, float v1z,
                   float v2x, float v2y, float v2z,
                   float v3x, float v3y, float v3z);
  void paintDisplayList();
  void setMVPM(float p[16], float v[16]);
  void setTime(float timef);
 private:
		  
  GLSLProgram *shader;
  std::vector<MyVertex> vertices;
  std::vector<unsigned int> indices;
  GLuint vboIndex,vboID,pID;
  bool sh;
  static GLuint modelcount;
  GLuint mId;
  GLuint displayList;
  GLuint projM, viewM;
  GLuint tLoc;
};


#endif
