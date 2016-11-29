#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include "Mesh.h"
#include "Texture2D.h"

/*
	MESH_NAME and TEXTURE_NAME enums
	- Add a new name for each asset you add
	- This is what you will use to call the asset you want when pointing to it from a gameObject
	- Follow naming convention
		* all caps
		* mesh name prefix is MESH_XXXXX and texture name prefix is TEX_XXXXXX
*/
enum MESH_NAME
{
	MESH_BUS0,
	MESH_BUS1,
	MESH_BUS2,
	MESH_BUS3,
	MESH_BUS4,
	MESH_PASSENGER_A,
	MESH_PASSENGER_B,
	MESH_PASSENGER_C,
	MESH_LEVELPLAY,
	MESH_LEVELBACKGROUND,
	MESH_LEVELBACKGROUNDM,
	MESH_LEVELUNDERGROUND,
	MESH_BASEBUILDING,
	MESH_BOARDBUILDING,
	MESH_BILLBOARD,
	MESH_SIDEWALK,
	MESH_ROADBLOCK,
	MESH_SKYBOX,
	MESH_CROWN,
	MESH_CAR,
	MESH_QUAD,
	MESH_CLOCKTOWER,
	MESH_TUTORIALBILLBOARD,
	MESH_GARAGE_LEFT,
	MESH_GARAGE_RIGHT,

	NUM_MESHES
};

enum TEXTURE_NAME
{
	TEX_BUS0_RED,
	TEX_BUS0_BLUE,
	TEX_BUS0_GREEN,
	TEX_BUS0_YELLOW,
	TEX_BUS1_RED,
	TEX_BUS1_BLUE,
	TEX_BUS1_GREEN,
	TEX_BUS1_YELLOW,
	TEX_BUS2_RED,
	TEX_BUS2_BLUE,
	TEX_BUS2_GREEN,
	TEX_BUS2_YELLOW,
	TEX_BUS3_RED,
	TEX_BUS3_BLUE,
	TEX_BUS3_GREEN,
	TEX_BUS3_YELLOW,
	TEX_BUS4_RED,
	TEX_BUS4_BLUE,
	TEX_BUS4_GREEN,
	TEX_BUS4_YELLOW,
	TEX_PASSENGER,
	TEX_PASSENGER_2,
	TEX_PASSENGER_3,
	TEX_LEVELPLAY,
	TEX_LEVELBACKGROUND,
	TEX_LEVELBACKGROUNDM,
	TEX_LEVELUNDERGROUND,
	TEX_BASEBUILDING1,
	TEX_BASEBUILDING2,
	TEX_BASEBUILDING3,
	TEX_BASEBUILDING4,
	TEX_BOARDBUILDING1,
	TEX_BOARDBUILDING2,
	TEX_BOARDBUILDING3,
	TEX_BOARDBUILDING4,
	TEX_BILLBOARD1,
	TEX_BILLBOARD2,
	TEX_BILLBOARD3,
	TEX_BILLBOARD4,
	TEX_SIDEWALK,
	TEX_BACKGROUNDSIDEWALK,
	TEX_ROADBLOCK,
	TEX_FONT,
	TEX_SKYBOX,
	TEX_CROWN,
	TEX_MENU,
	TEX_FILLBAR,
	TEX_BILLBOARD,
	TEX_BILLBOARDLIGHTS,
	TEX_CLOCK,
	TEX_CAR,
	TEX_CLOCKTOWER,
	TEX_TUT_PLAYER_INDICATOR,
	TEX_TUT_BILLBOARD1,
	TEX_TUT_BILLBOARD2,
	TEX_TUT_START,
	TEX_GAMEPLAY_LEVELNAME,
	TEX_GAMEPLAY_COUNTDOWN_3,
	TEX_GAMEPLAY_COUNTDOWN_2,
	TEX_GAMEPLAY_COUNTDOWN_1,
	TEX_GAMEPLAY_COUNTDOWN_GO,
	TEX_LIGHTOVERLAY,
	TEX_GARAGE_LEFT,
	TEX_GARAGE_RIGHT,
	TEX_TUT_GROUND,
	TEX_TUT_GROUNDBACK,

	NUM_TEXTURES
};

/*
	AssetManager class
	- Follows singleton pattern (see note below)
	- Has every mesh and every texture used in the game, loaded in at the beginning
	- GameObjects will have a Mesh* and Texture* which will point to that asset here
	- This class will ensure all assets are only loaded in once but can be used my multiple things
	- Meshes and textures will have prefixes that should be followed
	- The list of assets is in the cpp in the loadAssets function

	Note:
	MUST CALL like this: AM::assets()->
	Do not make another instance of this class!

	How to add a new asset:
	- Make sure that meshes are exported as obj's and textures are exported as png's
	- Name asset according to the convention (mesh_XXXX.obj / tex_XXXX.png)
	- Put mesh in /res/mesh and textures in /res/img
	- Add asset name into the appropriate enum using that naming convention
	- Call vector.push_back with the appropriate constructor in the brackets Ex: loadedMeshes.push_back(Mesh("./res/mesh/mesh_Monkey.obj") OR loadedTextures.push_back("./res/img/tex_Monkey.png")
	- Ensure the push_back call is under the correct heading
	- OPTIONAL: Create GameObject using the constructor that takes a mesh and a texture (along with other params) like so: GameObject object(- other params -, MESH_MONKEY, TEX_MONKEY));
	- You should be good to go!
*/
class AssetManager
{
protected:
	AssetManager(); //Protected constructor for singleton pattern

public:
	~AssetManager(); //Destructor, currently doesn't do anything

	Mesh& getMesh(MESH_NAME meshName); //Returns a reference to the desired mesh, this is what allows for the mesh to be loaded once but used multiple times
	Texture2D& getTexture2D(TEXTURE_NAME textureName); //Returns a reference to desired texture, this is what allows for the texture to be loaded once but used multiple times

	void loadAssets(); //Called in main(), actually loads in and sets up all of the assets that will be used in the game
	void bindTexture(TEXTURE_NAME textureName); //Binds the texture that will be used for the next drawing calls

	static AssetManager* assets(); //Singleton pattern

private:
	static AssetManager* inst; //Singleton pattern
	std::vector<Mesh> loadedMeshes; //Vector of all of the meshes in the game, should be in .obj format
	std::vector<Texture2D>loadedTextures; //Vector of all of the textures in the game, should be in .png format
};

typedef AssetManager AM; //Typedef in order to make calling the singleton easier

#endif
