#include "AssetManager.h"
#include "ShaderManager.h"
#include "GL\glew.h"
#include "GLUT\glut.h"

AssetManager* AssetManager::inst = 0; //The singleton instance of this class

//Constructor, pre-allocates space in the vectors for the number of meshes and textures in the game, saves time
AssetManager::AssetManager()
{
	loadedMeshes.reserve(NUM_MESHES);
	loadedTextures.reserve(NUM_TEXTURES);

	activeVBO = 0;
}

//Destructor, currently does nothing
AssetManager::~AssetManager()
{
}

/*
	Actually loads in the assets
	Notice the naming conventions!
	Add assets in EXACT order as specified in the enums
*/
void AssetManager::loadAssets()
{
	/* ========== MESHES (Naming: mesh_XXXXXX.obj) ========== */
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus2.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Level.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Passenger.obj"));
	
	/* ========== TEXTURES (Naming: tex_XXXXXX.png) ========== */
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus_Yellow.png"));	
	loadedTextures.push_back(Texture2D("./res/img/tex_Level.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Passenger.png"));

	/* ========== Generate VBO's For Meshes ========== */
	for (unsigned int i = 0; i < loadedMeshes.size(); i++)
	{
		//Gets the vertex data and then sets up the sub-vectors for the vertex attributes
		std::vector<Vertex> meshVertices = loadedMeshes[i].getVertices();
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec3> vertexNormals;
		std::vector<glm::vec2> uvCoords;

		//Copies the mesh data into the vertex attribute arrays so we can create VBO's and also enable the attributes
		for (unsigned int j = 0; j < meshVertices.size(); j++)
		{
			vertexPositions.push_back(meshVertices[i].position);
			vertexNormals.push_back(meshVertices[i].normal);
			uvCoords.push_back(meshVertices[i].uvCoord);
		}

		//Create the new VBO with the data subdivided into the various attributes. Need to allocate enough space for all of the different data types together
		GLuint newVBO;
		glGenBuffers(1, &newVBO);
		glBindBuffer(GL_ARRAY_BUFFER, newVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions) + sizeof(vertexNormals) + sizeof(uvCoords), NULL, GL_STATIC_DRAW);

		//Set up the vertex position subdivision within the array buffer...starts at the first (0) position and it requires
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions.data());

		//Set up the vertex normal subdivision within the array buffer...need to start at the end of the position data and it requires the size of the normal array
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexNormals), vertexNormals.data());

		//Set up the vertex uv coords subdivision within the array buffer...need to start at the end of the vertex position data which is that plus the position data and it requires the size of the uv data
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions) + sizeof(vertexNormals), sizeof(uvCoords), uvCoords.data());

		//Points to the position data in the buffer so that glsl knows what the position in the shader should be
		GLuint vPosition = glGetAttribLocation(SM::shaders()->getActiveShader(), "v_Position_In");
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(vPosition);

		//Points to the normal data in the buffer so that glsl knows what the normal in the shader should be
		GLuint vNormal = glGetAttribLocation(SM::shaders()->getActiveShader(), "v_Normal_In");
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vertexPositions)));
		glEnableVertexAttribArray(vNormal);

		//Points to the uv data in the buffer so that glsl knows what the uv in the shader should be
		GLuint vUV = glGetAttribLocation(SM::shaders()->getActiveShader(), "v_UV_In");
		glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vertexPositions) + sizeof(vertexNormals)));
		glEnableVertexAttribArray(vUV);

		//Unbinds the VBO now that it has been set up
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Adds the VBO to the vector
		meshVBOs.push_back(newVBO);
	}
}

void AssetManager::bindTexture(TEXTURE_NAME textureName)
{
	loadedTextures[textureName].bind();
}

void AssetManager::bindMesh(MESH_NAME meshName)
{
	activeVBO = meshName;
	glBindBuffer(GL_ARRAY_BUFFER, meshVBOs[meshName]);
}

//Returns a reference to the desired mesh, allows for multiple objects to use the same mesh with only one loading time
Mesh& AssetManager::getMesh(MESH_NAME meshName)
{
	try 
	{
		return loadedMeshes.at(meshName); //Returns the address of the mesh stored within the vector
	}
	catch (std::out_of_range) //Error catching
	{
		std::cout << "Error! The mesh requested is out of bounds of the vector! Aborting!" << std::endl;
		abort();
	}
	catch (...)
	{
		std::cout << "Unknown error when trying to get the mesh! Aborting!" << std::endl;
		abort();
	}
	
}

//Returns a reference to the desired texture, allows for multiples objects to use the same texture with only one loading time
Texture2D& AssetManager::getTexture2D(TEXTURE_NAME textureName)
{
	try 
	{
		return loadedTextures.at(textureName); //Returns the address of the texture stored within the vector
	}
	catch (std::out_of_range) //Error catching
	{
		std::cout << "Error! The texture requested is out of bounds of the vector! Aborting!" << endl;
		abort();
	}
	catch (...)
	{
		std::cout << "Unknown error when trying to get the texture! Aborting!" << std::endl;
		abort();
	}
}

int AssetManager::getNumVerticesInActiveVBO() const
{
	return loadedMeshes[activeVBO].getNumVertices();
}

/* Singleton Pattern */
AssetManager* AssetManager::assets()
{
	if (!inst)
		inst = new AssetManager();

	return inst;
}