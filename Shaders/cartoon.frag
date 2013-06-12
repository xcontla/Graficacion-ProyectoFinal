#version 120
varying vec3 normal;
void main(void)
{
 // Compute light direction
 vec3 ld = normalize( vec3( gl_LightSource[0].position) );
 // Compute light intensity to the surface
 float ity = dot( ld, normal );
 // Weight the final color in four cases, dependeing on the light intensity
 vec4 fc;
 if(ity > 0.95) fc = 1.00 * gl_Color;
 else if(ity > 0.50) fc = 0.50 * gl_Color;
 else if(ity > 0.25) fc = 0.25 * gl_Color;
 else fc = 0.10 * gl_Color;
 // Output the finale color
 gl_FragColor = fc;
}

