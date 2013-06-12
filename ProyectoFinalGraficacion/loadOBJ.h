//#define GL_GLEXT_PROTOTYPES
#ifndef LOADOBJ_H
#define LOADOBJ_H
#include <GL/glew.h>
#include <GL/glut.h>
#include "glext.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "glInfo.h"
#include <vector>
#include <string>
#include <cmath>
#include  "xcstructures.h"
#include "glslProgram.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


typedef float vec3_t[3];
typedef float vec4_t[4];

/* Vertex */
struct obj_vertex_t
{
        vec4_t xyzw;
};

/* Texture coordinates */
struct obj_texCoord_t
{
        vec3_t uvw;
};

/* Normal vector */
struct obj_normal_t
{
        vec3_t ijk;
};

/* Polygon */
struct obj_face_t
{
        GLenum type;        /* primitive type */
    int num_elems;      /* number of vertices */

        int *vert_indices;  /* vertex indices */
        int *uvw_indices;   /* texture coordinate indices */
        int *norm_indices;  /* normal vector indices */
};

/* OBJ model structure */
struct obj_model_t
{
        int num_verts;                     /* number of vertices */
        int num_texCoords;                 /* number of texture coords. */
        int num_normals;                   /* number of normal vectors */
        int num_faces;                     /* number of polygons */

        int has_texCoords;                 /* has texture coordinates? */
        int has_normals;                   /* has normal vectors? */

        struct obj_vertex_t *vertices;     /* vertex list */
        struct obj_texCoord_t *texCoords;  /* tex. coord. list */
        struct obj_normal_t *normals;      /* normal vector list */
        struct obj_face_t *faces;          /* model's polygons */
};


/*
typedef struct
{
  float x, y, z;        //Vertex
  float nx, ny, nz;     //Normal
  float s0, t0;         //Texcoord0
  float r,g,b;
}MyVertex;*/

class LoadOBJ
{
 public:
  struct obj_model_t mdl;
  std::vector< MyVertex > vboS;
  std::vector< unsigned int > m_indices;
  int numIndices;
  int numVertices;
  float xlow,xhigh,ylow,yhigh,zlow, zhigh;
  
  LoadOBJ(const char *filename,GLuint m);
  
  void FreeModel ();
  int MallocModel ();
  int FirstPass (FILE *fp);
  int SecondPass (FILE *fp);
  int ReadOBJModel (const char *filename);
  void RenderOBJModel ();
  void passToVBO();
  void initVBO();
  void renderOBJ();
  bool putBindAttribLocationFor();
  void initShader(std::string vertexShaderFile, std::string fragmentShaderFile);
  void activeShader();
  void disactiveShader();
  void setMVPM(float p[16], float v[16]);
  void setTime(float timef);
  GLSLProgram* getShader(){return shader;}
  GLuint getShaderID(){return pID;}


private:
  GLuint vboId, vboIndex;
  GLuint mid;
  GLSLProgram *shader;
  GLuint pID;
  GLuint projM, viewM;
  GLuint tLoc;

};
#endif

