#pragma once
#include "glm\glm.hpp"
#include "GLUT\glut.h"
#include "glm\gtx\rotate_vector.hpp"


struct Col_Sphere
{
	Col_Sphere(glm::vec3 pos, float rad) : position(pos), radius(rad) {}
	glm::vec3 position;
	float radius;
};

struct Col_AABB
{
	Col_AABB(glm::vec3 pos, glm::vec3 ext) : position(pos), extent(ext) {}
	glm::vec3 position;
	glm::vec3 extent;
};

struct Col_OBB
{
	Col_OBB() {}
	Col_OBB(glm::vec3 pos, glm::vec3 ext) : position(pos), extent(ext) {}
	glm::vec3 position;
	glm::vec3 extent;
	glm::vec3 rotation;
};

static void drawCollisionBox(const Col_OBB& boxToDraw, glm::vec3 colour)
{
	//temporary thing, header didn't like having DH included, bleh
	float degreestoradians = 57.2957795f;
	//Calculate points
	glm::vec3 vertices[8];
	vertices[0] = glm::vec3(boxToDraw.position + glm::vec3(boxToDraw.extent.x, boxToDraw.extent.y, boxToDraw.extent.z));
	vertices[1] = glm::vec3(boxToDraw.position + glm::vec3(boxToDraw.extent.x, boxToDraw.extent.y, -boxToDraw.extent.z));
	vertices[2] = glm::vec3(boxToDraw.position + glm::vec3(boxToDraw.extent.x, -boxToDraw.extent.y, boxToDraw.extent.z));
	vertices[3] = glm::vec3(boxToDraw.position + glm::vec3(-boxToDraw.extent.x, boxToDraw.extent.y, boxToDraw.extent.z));
	vertices[4] = glm::vec3(boxToDraw.position + glm::vec3(-boxToDraw.extent.x, -boxToDraw.extent.y, boxToDraw.extent.z));
	vertices[5] = glm::vec3(boxToDraw.position + glm::vec3(-boxToDraw.extent.x, boxToDraw.extent.y, -boxToDraw.extent.z));
	vertices[6] = glm::vec3(boxToDraw.position + glm::vec3(boxToDraw.extent.x, -boxToDraw.extent.y, -boxToDraw.extent.z));
	vertices[7] = glm::vec3(boxToDraw.position + glm::vec3(-boxToDraw.extent.x, -boxToDraw.extent.y, -boxToDraw.extent.z));

	//Draw points
	glColor3f(colour.x, colour.y, colour.z);
	glPointSize(10.0f);

	glBegin(GL_POINTS);
	{
		//Broken in a way that works, it's rotating all of the vertices around the origin. 
		for (int i = 0; i < 8; i++)
		{
			//this needs to rotate around itself, not origin
			vertices[i] = glm::rotate(vertices[i], boxToDraw.rotation.x / degreestoradians, glm::vec3(1, 0, 0));
			vertices[i] = glm::rotate(vertices[i], boxToDraw.rotation.y / degreestoradians, glm::vec3(0, 1, 0));
			vertices[i] = glm::rotate(vertices[i], boxToDraw.rotation.z / degreestoradians, glm::vec3(0, 0, 1));
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
	}
	glEnd();
	glPointSize(1.0f);
}

static void drawCollisionBox(glm::vec4* vertices, glm::vec3 colour)
{
	//Draw points
	glColor3f(colour.x, colour.y, colour.z);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < 8; i++)
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
	glPointSize(1.0f);
}