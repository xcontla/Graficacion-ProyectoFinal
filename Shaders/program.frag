//reset values Fragment Shader
#version 150
in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vPosition;

out vec4 outputF;

void main(void)
{
  vec3 LightSourcePos = vec3(0.0,1.0,0.0);

  vec3 v = vPosition;
  vec3 N = vColor;
  vec4 As = vec4(0.1, 0.1, 0.1, 1.0 );
  vec3 L = normalize(LightSourcePos.xyz - v);
  vec3 E = normalize(-v);
  vec3 R = normalize(-reflect(L,N));

  vec4 Iamb  = vec4(0.0,0.0,0.0,1.0);
  vec4 Idiff = clamp(vec4(1.0,1.0,1.0,1.0) * max(dot(N,L), 0.0), 0.0, 1.0 ) ;

  vec4 Ispec = clamp( vec4(1.0,1.0,1.0,0.0)
		      * pow(max(dot(R,E),0.0), 100.0), 0.0, 1.0 ) ;


  vec4 color = vec4(vColor,1.0);
  Idiff = (color * Idiff);
  Iamb = (color * Iamb)+(color * As);

  vec4 texel = Iamb + Idiff;
  
  
  outputF = clamp(texel, 0.0, 1.0 ) ;
  //vec3 color = clamp(vColor,0.0,1.0);
  //outputF= vec4(color,1.0);

   
}
