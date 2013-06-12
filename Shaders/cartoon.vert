#version 120
varying vec3 normal;
void main(void)
{
 // Compute normal per-vertex
 normal = normalize(gl_NormalMatrix * gl_Normal);
 gl_FrontColor = gl_Color;
 // Transform position using built-in function
 gl_Position = ftransform();
}

