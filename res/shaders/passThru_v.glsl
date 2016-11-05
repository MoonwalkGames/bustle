/*
	Vertex Shader

	Uses GL's MVP stack to transform the incoming vertex.
*/

#version 330
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 normal;

out vec3 normal0;

uniform mat4 MVP_Matrix;

void main()
{
	normal0 = normal;
	gl_Position = MVP_Matrix * vec4(vPos, 1.0f);	//every vert shader must set gl_Position.....this line now sets the vertex position to be the transformed vertex position
}



