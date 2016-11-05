/*
	Basic Vertex Shader (pairs with shader_Base.frag)
	
	When shader program is complete, will have the following:
	- Basic lighting (with shadows?)
	- Texturing
*/
#version 330

uniform mat4 model; //Calculated in gameObject.update and passed here. Might be able to find a way to calculate this here instead-->maybe pass in the various matrices instead of the vectors?
uniform mat4 view; //Created in state.load or whenever the camera changes its positions. Essentially created from lookAt
uniform mat4 projection; //Created in state.load and passed here then. Only changed if the perspective / ortho set up is changed

in vec3 v_Position_In; //Vertex position, passed in by VBO
in vec3 v_Normal_In; //Vertex normal, passed in by VBO
in vec2 v_UV_In; //Vertex tex coord, passed in by VBO

out vec3 v_Normal_Out; //Vertex normal out, passed on for lighting
out vec2 v_UV_Out; //Vertex tex coord, passed on for texturing

void main()
{
	vec4 position = vec4(v_Position_In, 1.0f);
	gl_Position = projection * model * view * position; //Sets the position of the vertices

	v_Normal_Out = v_Normal_In; //Passes on the data
	v_UV_Out = v_UV_In;
}