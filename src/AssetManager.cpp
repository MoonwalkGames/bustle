#include "AssetManager.h"

AssetManager* AssetManager::inst = 0; //The singleton instance of this class

//Constructor, pre-allocates space in the vectors for the number of meshes and textures in the game, saves time
AssetManager::AssetManager()
{
	loadedMeshes.reserve(NUM_MESHES);
	loadedTextures.reserve(NUM_TEXTURES);
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
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus0.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus1.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus2.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus3.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Bus4.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Passenger_A.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Passenger_B.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Passenger_C.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_LevelArea.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_LevelBackground.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_LevelBackgroundM.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_LevelUnderground.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_BaseBuilding.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_BoardBuilding.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Billboard.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_LevelSidewalk.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Roadblock.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Skybox.obj"));
	loadedMeshes.push_back(Mesh("./res/mesh/mesh_Crown.obj"));
	
	/* ========== TEXTURES (Naming: tex_XXXXXX.png) ========== */
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus0_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus0_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus0_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus0_Yellow.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus1_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus1_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus1_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus1_Yellow.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus2_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus2_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus2_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus2_Yellow.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus3_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus3_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus3_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus3_Yellow.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus4_Red.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus4_Blue.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus4_Green.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Bus4_Yellow.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Passenger.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Passenger_2.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_LevelArea.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_LevelBackground.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_LevelBackgroundM.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Underground.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BaseBuilding1.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BaseBuilding2.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BaseBuilding3.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BaseBuilding4.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BoardBuilding1.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BoardBuilding2.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BoardBuilding3.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BoardBuilding4.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Billboard1.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Billboard2.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Billboard3.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Billboard4.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_LevelSidewalk.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_LevelBackgroundSidewalk.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Roadblock.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Font.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Skybox.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Crown.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Menu.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_FillBar.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Billboard.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_BillboardLights.png"));
	loadedTextures.push_back(Texture2D("./res/img/tex_Clock.png"));
}

void AssetManager::bindTexture(TEXTURE_NAME textureName)
{
	//glBindTexture(GL_TEXTURE_2D, NULL);
	loadedTextures[textureName].bind();
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

std::vector<Face>& AssetManager::getMeshFaces(MESH_NAME meshName)
{
	return loadedMeshes[meshName].faces;
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

/* Singleton Pattern */
AssetManager* AssetManager::assets()
{
	if (!inst)
		inst = new AssetManager();

	return inst;
}