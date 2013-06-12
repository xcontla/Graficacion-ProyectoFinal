#ifndef STRUCT_H
#define STRUCT_H


typedef struct
{
  float x, y, z;        //Vertex
  float nx, ny, nz;
  float s0, t0;         //Texcoord0
  float r,g,b;
}MyVertex;


enum AttributeSlot {
  SlotPosition,
  SlotNormal,
  SlotTexCoord,
  SlotColor
  };

#endif
