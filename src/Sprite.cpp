#pragma once
#include "Sprite.h"
#include "DebugManager.h"

Sprite::Sprite()
	: Kinematic()
{
	mesh = 0;
	texture = 0;
	numFramesX = 0;
	numFramesY = 0;

	//Adds the single frame to the list and sets it as active
	SpriteFrame spr;
	spr.uMin = 0.0f;
	spr.uMax = 1.0f;
	spr.vMin = 0.0f;
	spr.vMax = 1.0f;
	frames.push_back(spr);

	activeFrameNumX = 0;
	activeFrameNumY = 0;
	activeFrame = frames[0];
}

Sprite::Sprite(TEXTURE_NAME _texture, int numColoumns, int numRows)
	: Kinematic()
{
	mesh = 0; //Makes the mesh pointer within the parent gameobject to be null. This ensures we only render the quad as defined below
	texture = &AM::assets()->getTexture2D(_texture);

	numFramesX = numColoumns;
	numFramesY = numRows;

	glm::vec2 spriteSheetSize = glm::vec2(texture->getTextureWidth(), texture->getTextureHeight());
	glm::vec2 spriteFrameSize = glm::vec2(spriteSheetSize.x / float(numColoumns), spriteSheetSize.y / float(numRows));
	glm::vec2 spriteFrameSizeNormalized = glm::vec2(spriteFrameSize.x / spriteSheetSize.x, spriteFrameSize.y / spriteSheetSize.y);

	//Adds all of the sprite frames to the list
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColoumns; j++)
		{
			SpriteFrame spr;
			spr.uMin = j * spriteFrameSizeNormalized.x;
			spr.uMax = j * spriteFrameSizeNormalized.x + spriteFrameSizeNormalized.x;
			spr.vMax = 1 - (spriteFrameSizeNormalized.y * i);
			spr.vMin = 1 - (spriteFrameSizeNormalized.y * i) - spriteFrameSizeNormalized.y;
			frames.push_back(spr);
		}
	}

	activeFrame = frames[0];

	cameraPosition = glm::vec3(0.0f);
	cameraLookAtPosition = glm::vec3(0.0f);
	billboard = false;
}

Sprite::Sprite(TEXTURE_NAME texture, int numColoumns, int numRows, glm::vec3 cameraPos, glm::vec3 cameraLookAtPos)
	: Sprite(texture, numColoumns, numRows)
{
	billboard = true;
	cameraPosition = cameraPos;
	cameraLookAtPosition = cameraLookAtPos;
}

Sprite::~Sprite()
{
}

void Sprite::rotateForBillboard()
{
	setForwardVector(cameraPosition - cameraLookAtPosition);
	addToRotation(0.0f, 90.0f, 0.0f); //Has to rotate an extra 90 degrees because our forward vector is actually on the x but open gl uses Z
}

void Sprite::update(float dt)
{
	float degToRad = 3.1415f / 180.0f;

	// ----- Create the local to world matrix. Can't do this with gameobject since this has its own special mesh ------ //
	//Create the scaling matrix
	glm::mat4 scaleMatrix = glm::scale(scale);

	//Rotates the sprite if it is a billboard
	if (billboard)
		rotateForBillboard();

	//Create the individual rotation matrices and then the concatenated one
	glm::mat4 rotMatrix_X = glm::rotate(degToRad * rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotMatrix_Y = glm::rotate(degToRad * rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotMatrix_Z = glm::rotate(degToRad * rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 fullRotationMatrix = rotMatrix_X * rotMatrix_Y * rotMatrix_Z;

	//Create the translation matrix
	glm::mat4 translationMatrix = glm::translate(position);

	//Compiles the transformation together in the correct order: Scale -> Rotate -> Translate (Note the right to left notation)
	localToWorld = translationMatrix * fullRotationMatrix * scaleMatrix;

	//Passes the matrix to OpenGL which automatically applies the transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(localToWorld));

	// ----- Draw the sprite ----- //
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	//Draw the sprite
	glBegin(GL_QUADS);
	{
		glTexCoord2f(activeFrame.uMin, activeFrame.vMin); glVertex3f(-0.5f, -0.5f, 0.0f);
		glTexCoord2f(activeFrame.uMax, activeFrame.vMin); glVertex3f(0.5f, -0.5f, 0.0f);
		glTexCoord2f(activeFrame.uMax, activeFrame.vMax); glVertex3f(0.5f, 0.5f, 0.0f);
		glTexCoord2f(activeFrame.uMin, activeFrame.vMax); glVertex3f(-0.5f, 0.5f, 0.0f);
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	if (DBG::debug()->getVisualDebugEnabled())
		debugDraw(dt);

	glLoadIdentity();
}

void Sprite::debugDraw(float dt)
{
	Kinematic::drawDebug(dt);
}

void Sprite::nextFrame()
{
	activeFrameNumX++;

	if (activeFrameNumX > numFramesX)
	{
		activeFrameNumX = 0;
		activeFrameNumY++;
	}

	if (activeFrameNumY > numFramesY)
		activeFrameNumY = 0;
}

void Sprite::setActiveFrame(int frameNumber)
{
	if (frameNumber > frames.size())
	{
		std::cout << "ERROR! Requested sprite frame is out of bounds! Aborting!" << std::endl;
		abort();
	}

	activeFrame = frames[frameNumber];
}

void Sprite::setCameraPos(glm::vec3 cameraPos, glm::vec3 cameraLookAtPos)
{
	cameraPosition = cameraPos;
	cameraLookAtPosition = cameraLookAtPos;
}

std::vector<Sprite> Sprite::createTextVector(TEXTURE_NAME fontSheet, float posX, float posY, float scaleX, float scaleY, std::string text)
{
	std::vector<Sprite> textVector;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		Sprite spr = Sprite(fontSheet, 16, 8);
		spr.setActiveFrame(text.at(i));
		spr.setPosition(glm::vec3(posX + (4 * spr.getScale().x * i), posY, 1.0f));
		spr.setScale(scaleX, scaleY, 1.0f);
		textVector.push_back(spr);
	}

	return textVector;
}

std::vector<Sprite> Sprite::createTextVector(TEXTURE_NAME fontSheet, float posX, float posY, float scaleX, float scaleY, std::string text, glm::vec3 cameraPos, glm::vec3 cameraLookAtPos)
{
	std::vector<Sprite> textVector;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		Sprite spr = Sprite(fontSheet, 16, 8, cameraPos, cameraLookAtPos);
		spr.setActiveFrame(text.at(i));
		spr.setScale(scaleX, scaleY, 1.0f);
		spr.setPosition(glm::vec3(posX + (spr.getScale().x * i), posY, 0.0f));
		textVector.push_back(spr);
	}

	return textVector;
}

std::vector<Sprite> Sprite::changeTextVector(TEXTURE_NAME fontSheet, std::vector<Sprite> text, string newText)
{
	if (text.size() != newText.length())
	{
		cout << "Error! New text size does not match original size! Aborting!" << endl;
//		abort();
	}
	else
	{
		for (unsigned int i = 0; i < text.size(); i++)
			text[i].setActiveFrame(newText[i]);
	}

	return text;
}

void Sprite::drawTextVector(std::vector<Sprite> textSprites, float dt)
{
	for (unsigned int i = 0; i < textSprites.size(); i++)
		textSprites[i].update(dt);
}