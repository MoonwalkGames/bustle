/*
	Shader class that represents a shader program (has a vert and a frag shader)
	Created and provided by Thomas Galati
*/

#pragma once
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char *, const char *);
	~Shader(void);

	void init(const char *, const char *);

	void bind();		// use the shader vert and frag
	void unbind();		// stop using shader vert and frag

	unsigned int getID();

	void uniformVector(const char*, float*);
	void uniformVector(const char*, float, float, float);
	void uniformFloat(const char*, float );
	void uniformTex(const char*, GLuint , unsigned short);

	//------------------------------------------------------------------------
	// Variables

	//glsl program handler
	unsigned int programID;

	//vert and fag shaders
	unsigned int vertShader;
	unsigned int fragShader;


};
