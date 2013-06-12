#version 120

varying vec4 position;
varying vec3 normal;

void main(void)
{
	position = gl_ModelViewMatrix * gl_Vertex;
	normal = gl_NormalMatrix * gl_Normal;

	// normal MVP transform
	gl_Position = ftransform();
}

