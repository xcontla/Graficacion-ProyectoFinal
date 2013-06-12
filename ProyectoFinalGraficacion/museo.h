#ifndef MYTEXTURE_H
#define MYTEXTURE_H
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include "texture.hpp"
#define NUMTEXTURES 5



class Museo{
private:
    //const int numTextures = NUMTEXTURES;

    static GLfloat museumBlanco[];
    static GLfloat museumEmission[];
    static GLfloat museumNegro[];



public:

    Museo();
    ~Museo();
    void initTextureMuseum();
    void drawMuseum();
    void clearSharedMemMuseum();
    void setTheMaterial( const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular,const GLfloat *emission);
};
#endif
