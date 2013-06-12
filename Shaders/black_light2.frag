varying vec4 position;
varying vec3 normal;

void main(void)
{
	vec4 fullVector = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 color = gl_FrontMaterial.emission + (fullVector - (fullVector - gl_FrontMaterial.ambient)*gl_LightModel.ambient);
	for(int i = 0; i < 8; i++)
	{
		vec4 L = normalize(gl_LightSource[i].position - position);
		vec4 s = normalize(L + vec4(0f, 0f, 1f, 0f));
		vec4 v = -L;
		vec4 d = vec4(gl_LightSource[i].spotDirection, 0f);

		float attenuation = 1.0f;
		float spotlightEffect = 1.0f;

		if(gl_LightSource[i].position.w != 0.0f)
			attenuation = 1.0f/(gl_LightSource[i].constantAttenuation + gl_LightSource[i].linearAttenuation*length(L) 
					    + gl_LightSource[i].quadraticAttenuation*length(L)*length(L));

		if(gl_LightSource[i].spotCutoff != 180.0f)
		{
			if(max(0f, dot(v, d)) == 0.0f)
				continue;

			spotlightEffect = max(0f, dot(v, d))*gl_LightSource[i].spotExponent;
		}

		color += attenuation*spotlightEffect * ((fullVector - (fullVector - gl_FrontMaterial.ambient)*gl_LightSource[i].ambient) + max(0f, dot(L, vec4(normal, 0.0f)))*(fullVector - (fullVector - gl_FrontMaterial.diffuse)*gl_LightSource[i].diffuse) + max(0f, dot(s, vec4(normal, 0.0f)))*gl_FrontMaterial.shininess * (fullVector - (fullVector - gl_FrontMaterial.specular)*gl_LightSource[i].specular));
	}

	gl_FragColor = clamp(color, 0f, 1f);
}

