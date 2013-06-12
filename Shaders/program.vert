#version 150
in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
in vec3 in_Color;

uniform mat4 viewMatrix, projMatrix;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vColor;


void main(void)
{

  vPosition = in_Position;
  vTexCoord = in_TexCoord;
  vColor = in_Color;

  gl_Position = projMatrix * viewMatrix * vec4(vPosition,1.0);
  
}
