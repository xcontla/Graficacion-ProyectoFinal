#version 120
varying vec3 n;
varying vec3 p;
void main (void)
{
 // we are in Eye Coordinates, so EyePos is (0,0,0)
 vec3 L = normalize(gl_LightSource[0].position.xyz - p);
 vec3 E = normalize(-p);
 vec3 R = normalize(-reflect(L,n));
 //calculate Ambient Term:
 vec4 Iamb = gl_FrontLightProduct[0].ambient;
 //calculate Diffuse Term:
 vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(n,L), 0.0);
 // calculate Specular Term:
 vec4 Ispec = gl_FrontLightProduct[0].specular *
                                      pow(max(dot(R,E),0.0), gl_FrontMaterial.shininess);
 // write Total Color:
 gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;
}

