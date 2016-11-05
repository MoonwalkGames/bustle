#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include "Shader.h"

/*
	SHADER_NAME enum
	- Add a new name for each new shader program you make
	- Note: shader programs are made up of a vertex AND a fragment shader
	- Follow naming convention
		* all caps
		* prefix is SHADER_XXXXXX
*/
enum SHADER_NAME
{
	SHADER_BASE,

	NUM_SHADERS
};


/*
	ShaderManager class
	- Follows singleton pattern (see note below)
	- Has every shader used in the game
	- Call SM::shaders()->bindShader(SHADER_NAME) if you want to draw with a new shader
	- Shaders will have a naming convention that should be followed
		* shader_XXXXXXX.vert for vertex shader or shader_XXXXXX.frag for fragment shader
	- The shaders are loaded in the cpp of this class

	Note:
	MUST CALL like this: SM::shaders()->
	Do not make another instance of this class!
*/
class ShaderManager
{
protected:
	ShaderManager(); //Protected constructor for singleton pattern

public:
	~ShaderManager();

	Shader& getShader(SHADER_NAME shaderName); //Returns a reference to the shader program...will probably never really use this. Should bind shader instead

	void loadShaders(); //Called in main, loads, compiles, and links the shaders
	void bindShader(SHADER_NAME shaderName); //Sets the active shader to be drawn with
	void unbindShader(); //Unbinds shaders...probably shouldn't use except for cleanup at the end
	
	GLuint getActiveShader() const;

	static ShaderManager* shaders(); //Singleton pattern

private:
	static ShaderManager* inst; //Singleton pattern
	std::vector<Shader> loadedShaders; //Vector of all of the actual shaders loaded into the game
	GLuint activeShader;
};

typedef ShaderManager SM;

#endif