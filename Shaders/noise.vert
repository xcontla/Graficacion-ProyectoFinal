#version 150

uniform float time;

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
in vec3 in_Color;

uniform mat4 viewMatrix, projMatrix;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vColor;

/*
 * Both 2D, 3D and 4D texture coordinates are defined, for testing purposes.
 */
out vec2 v_texCoord2D;
//out vec3 v_texCoord3D;
//out vec4 v_texCoord4D;

void main( void )
{

  vPosition = in_Position;
  vTexCoord = in_TexCoord;
  vColor = in_Color;

  gl_Position = projMatrix * viewMatrix * vec4(vPosition,1.0)
/*gl_ModelViewProjectionMatrix * gl_Vertex*/;

	v_texCoord2D = vTexCoord * 16.0 + vec2(0.0, time);
	// v_texCoord3D = vec3(gl_MultiTexCoord0.xy * 16.0, time);
	// v_texCoord4D = vec4(gl_MultiTexCoord0.xy * 16.0, 0.0, time);
}
