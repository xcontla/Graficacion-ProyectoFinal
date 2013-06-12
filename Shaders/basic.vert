//#version 120
varying vec3 n;
varying vec3 p;
void main(void)
{
 p = vec3(gl_ModelViewMatrix * gl_Vertex);
 n = normalize(gl_NormalMatrix * gl_Normal);
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

