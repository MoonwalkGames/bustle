/*
	Fragment Shader

	Sets the fragment colour
*/

#version 330

in vec3 normal0;
in vec2 texCoord;
in vec3 color0;
in vec3 lightDirection;

uniform sampler2D tex1;
uniform float dispNormals;

void main()
{
	vec4 color;
	vec3 L = lightDirection;

	if(dispNormals == 0.0) // show only normals
	{
		color = vec4(color0, 1.0);
	}
	else //regular texture
	{
		color = texture2D(tex1, texCoord.st);//vec4(1.0, 0.0, 0.0, 1.0);
		float lightIntensity = clamp(dot(normal0, L), 0.0, 1.0);

		vec4 diffuse = color * lightIntensity;

		vec4 ambient = color * 0.05;

		color = diffuse + ambient;
	}

	color.w = 1.0;

	gl_FragColor = color; //every frag shader must set gl_FragColor
}