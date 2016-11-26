#pragma once
/*
Sprite class
*/

#include "Kinematic.h"

struct SpriteFrame
{
	float uMin, uMax;
	float vMin, vMax;
};

class Sprite : public Kinematic
{
public:
	Sprite();
	Sprite(TEXTURE_NAME texture, int numColoumns, int numRows); //for non-billboards
	Sprite(TEXTURE_NAME texture, int numColoumns, int numRows, glm::vec3 cameraPos, glm::vec3 cameraLookAtPos); //for billboards
	~Sprite();

	virtual void update(float dt);
	virtual void draw();
	virtual void debugDraw();

	void nextFrame();
	void setActiveFrame(int frameNumber);
	void setCameraPos(glm::vec3 cameraPos, glm::vec3 cameraLookAtPos);

	static std::vector<Sprite> Sprite::createTextVector(TEXTURE_NAME fontSheet, float posX, float posY, float scaleX, float scaleY, std::string text); //for non billboards
	static std::vector<Sprite> Sprite::createTextVector(TEXTURE_NAME fontSheet, float posX, float posY, float scaleX, float scaleY, std::string text, glm::vec3 cameraPos, glm::vec3 cameraLookAtPos); //for billboards
	static std::vector<Sprite> Sprite::changeTextVector(TEXTURE_NAME fontSheet, std::vector<Sprite> text, string newText);
	static void Sprite::drawTextVector(std::vector<Sprite> textSprites, float dt);

private:
	int numFramesX;
	int numFramesY;
	std::vector<SpriteFrame> frames;
	int activeFrameNumX, activeFrameNumY;
	SpriteFrame activeFrame;
	bool billboard;
	glm::vec3 cameraPosition, cameraLookAtPosition;

	void rotateForBillboard();
};