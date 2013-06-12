#version 120
varying vec4 position;
varying vec3 normal;

void main(void)
{
	vec4 color = gl_FrontLightModelProduct.sceneColor;
	for(int i = 0; i < 8; i++)
	{
		gl_LightProducts lightProducts = gl_FrontLightProduct[i];
		vec4 L = normalize(gl_LightSource[i].position - position);
		vec4 s = normalize(L + vec4(0.0, 0.0, 1.0, 0.0));
		vec4 v = -L;
		vec4 d = vec4(gl_LightSource[i].spotDirection, 0.0);

		float attenuation = 1.0;
		float spotlightEffect = 1.0;

		if(gl_LightSource[i].position.w != 0.0)
			attenuation = 1.0f/(gl_LightSource[i].constantAttenuation + gl_LightSource[i].linearAttenuation*length(L) + gl_LightSource[i].quadraticAttenuation*length(L)*length(L));

		if(gl_LightSource[i].spotCutoff != 180.0)
		{
			spotlightEffect = max(0.0, dot(v, d))*gl_LightSource[i].spotExponent;
		}

		color += attenuation*spotlightEffect * (lightProducts.ambient + max(0.0, dot(L, vec4(normal, 0.0)))*lightProducts.diffuse + max(0.0, dot(s, vec4(normal, 0.0)))*gl_FrontMaterial.shininess * lightProducts.specular);
	}

	/*	vec4 fullVector = vec4(255, 255, 255, 255);
		gl_FragColor = (fullVector - (fullVector - color)*255.0)/255;*/

	vec4 fullVector = vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = (fullVector - (fullVector - color)*1.0);
}

