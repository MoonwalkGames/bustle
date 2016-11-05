/*
	Fragment Shader

	Sets the fragment colour

	This is bad
*/

#version 330

in vec3 normal0;

void main()
{
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	
	float lightIntensity = dot(vec3(0.0f, 0.0f, 0.0f), normal0); //Calculates the dot product between this vertex normal and the world up vector for now to get a value from 0 to 1 which we will use to affect our colour
	vec4 diffuse = color * lightIntensity; //shades by multiplying the original colour by the result of the light intensity from above from 0 to 1
	
	vec4 outColour = diffuse; //will later add ambient, specular, etc
	outColour.w = 1.0f; //Ensure the alpha channel stays at fully opaque because otherwise the lightIntensity would also make the object invisible

	gl_FragColor = outColour; //every frag shader must set gl_FragColor
}