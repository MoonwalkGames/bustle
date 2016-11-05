/*
	Basic Fragment Shader (pairs with shader_Base.vert)
	
	When shader program is complete, will have the following:
	- Basic lighting (with shadows?)
	- In-shader MVP computation
	- Texturing
*/

#version 330

in vec3 v_Normal_Out; //Normal and Uv passed on by the vertex shader
in vec2 v_UV_Out;

void main()
{
	gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); //Sets the final colour of the fragment
}