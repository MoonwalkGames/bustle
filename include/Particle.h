#ifndef PARTICLE_H
#define PARTICLE_H

#include "Kinematic.h"
#include "AssetManager.h"

/*
	Simple particle struct
	Based off the kinematic class so affected by phsyics forces like gravity, impulse, etc
	Has a colour property but can also be given a texture or even a mesh (texture and mesh are null pointers until you set them)
	Lifetime is a time in seconds for how long the particles will be there until they 'die' and get reset to the emitter position
*/
struct Particle : public Kinematic
{
	Particle() : Kinematic() {}

	float maxLifetime = 1.0f;
	float timeAlive = 0.0f;
	glm::vec3 parentEmitterPosition;

	void update(float deltaTime)
	{
		timeAlive += deltaTime;

		Kinematic::update(deltaTime);
	}
};

/*
	Particle Emitter class
	The point where the particles will actually be created
	Takes the max number of particles that are allowed to be created at once
	Can also take the basic parameters for the particles it is going to render

	NOTE:
	The ranges work by passing the corresponding min and max into the random float generator
	So, the min.X will be passed along with the max.X and a random value between those will be generated
	This means that the min and max you pass are not LERP'd, they are used as ranges
	
	Ex: 
		There are 4 values in colourMin and 4 in colourMax
		The colour will have an x value randomly picked between colourMin.X and colourMax.X
		The colour will have a y value randomly picked between colourMin.Y and colourMax.Y
		etc
		..
		It was easier to do it this way than have: colourXRange, colourYRange, colourZRange, and colourWRange all stored as individual vec2's
*/
class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(glm::vec3 emitterPosition, int maxNumParticles);
	~ParticleEmitter();

	//Emitter setters
	void setParticleLimit(int newMax); //Doing this will clear the vector so expect a temporary break in the particle stream
	void setEmitterPosition(glm::vec3 newEmitterPosition);
	void setEmitterPosition(float x, float y, float z);
	void setActive(bool active);
	void setContinuous(bool continuous);

	//Particle attribute setters
	void setParticleLifeRange(float minLife, float maxLife);
	void setParticleVelRange(glm::vec3 minVelocity, glm::vec3 maxVelocity);
	void setParticleColourRange(glm::vec4 minColour, glm::vec4 maxColour);
	void setParticleMesh(MESH_NAME mesh);
	void setParticleTexture(TEXTURE_NAME texture);

	void setParticles(float minLife, float maxLife, glm::vec3 minVel, glm::vec3 maxVel, glm::vec4 minColour, glm::vec4 maxColour);
	void setParticles(float minLife, float maxLife, glm::vec3 minVel, glm::vec3 maxVel, glm::vec4 minColour, glm::vec4 maxColour, MESH_NAME mesh, TEXTURE_NAME texture);

	//Getters
	glm::vec3 getEmitterPosition() const;
	int getMaxNumParticles() const;
	bool getActive() const;
	bool getContinuous() const;

	//Interactive functions
	void applyForceToParticles(glm::vec3 impulseForce);
	void update(float deltaTime);
	void applyParticleValues(); //Need to call whenever you change one of the particle parameters (ie: change the mesh)..could put this in each edit function but inefficient

private:
	//Emitter variables
	glm::vec3 emitterPosition;
	int numParticles;
	bool active;
	bool continuous; //True means the particles respawn when they die, false means the particles are deleted when they die
	std::vector<Particle> particles;

	//Particle attributes
	glm::vec2 particleLifeRange; //Vec2 of floats..basically like having particleLifeRangeMin & Max
	
	glm::vec3 particleVel_Min; //Range of velocities that can the particle can be spawned with
	glm::vec3 particleVel_Max;

	glm::vec4 particleColour_Min; //Range of colours that the particle can be spawned with
	glm::vec4 particleColour_Max;
	
	MESH_NAME particleMesh; //Optional renderables
	TEXTURE_NAME particleTexture;

	//Utility functions
	void initParticles();
	void resetParticle(int index); //Much like init, but for a single particle only. Called whenever a particle dies and needs to be reset with new randomized values
};

#endif
