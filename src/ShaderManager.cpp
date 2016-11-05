#include "ShaderManager.h"

ShaderManager* ShaderManager::inst = 0; //The singleton instance of this class

ShaderManager::ShaderManager()
{
	activeShader = 0;
	loadedShaders.reserve(NUM_SHADERS); //Pre-allocates space in vectors for optimization
}

ShaderManager::~ShaderManager()
{
}

Shader& ShaderManager::getShader(SHADER_NAME shaderName)
{
	try {
		return loadedShaders.at(shaderName);
	}
	catch (std::out_of_range) //Error catching
	{
		std::cout << "Error! The shader requested is out of bounds of the vector! Aborting!" << std::endl;
		abort();
	}
	catch (...)
	{
		std::cout << "Unknown error when trying to get the shader! Aborting!" << std::endl;
		abort();
	}
}
/*
	Actually loads in the shaders
	Notice the naming conventions!
	Add assets in EXACT order as specified in the enums
*/
void ShaderManager::loadShaders()
{
	//Actually loads in the shaders
	loadedShaders.push_back(Shader("./res/shaders/shader_Base.vert", "./res/shaders/shader_Base.frag"));
	//loadedShaders.push_back(Shader("./res/shaders/passThru_V.glsl", "./res/shaders/passThru_f.glsl"));
}

void ShaderManager::bindShader(SHADER_NAME shaderName)
{
	activeShader = loadedShaders[shaderName].getID();
	glUseProgram(activeShader);
}

void ShaderManager::unbindShader()
{
	glUseProgram(0);
}

GLuint ShaderManager::getActiveShader() const {
	return activeShader;
}

/* Singleton pattern */
ShaderManager* ShaderManager::shaders()
{
	if (!inst)
		inst = new ShaderManager();

	return inst;
}