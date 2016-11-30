#include "Particle.h"
#include "MathHelper.h"

/* ===================================== Particle Emitter Class ======================================== */
/* --- Constructors & Destructor --- */
ParticleEmitter::ParticleEmitter()
{
	//Emitter attributes
	emitterPosition = glm::vec3(0.0f);
	numParticles = 0;
	active = false;
	continuous = true;

	//Particle attributes
	particleLifeRange = glm::vec2(0.0f);
	particleVel_Min = glm::vec3(0.0f);
	particleVel_Max = glm::vec3(0.0f);
	particleColour_Min = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particleColour_Max = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particleRotation_Min = glm::vec3(0.0f, 0.0f, 0.0f);
	particleRotation_Max = glm::vec3(0.0f, 0.0f, 0.0f);
	particleScaleRange = glm::vec2(1.0f, 1.0f);
	particleCameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	billboardParticles = false;

	//Optional renderables
	particleMesh = NUM_MESHES; //Essentially treated as NULL
	particleTexture = NUM_TEXTURES; //Essentially treated as NULL
}

ParticleEmitter::ParticleEmitter(glm::vec3 _emitterPosition, int maxNumParticles)
{
	//Emitter attributes
	emitterPosition = _emitterPosition;
	numParticles = maxNumParticles;
	active = true;
	continuous = true;

	//Particle attributes
	particleLifeRange = glm::vec2(1.0f, 2.0f);
	particleVel_Min = glm::vec3(-1.0f, -1.0f, -1.0f);
	particleVel_Max = glm::vec3(1.0f, 1.0f, 1.0f);
	particleColour_Min = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particleColour_Max = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particleRotation_Min = glm::vec3(0.0f, 0.0f, 0.0f);
	particleRotation_Max = glm::vec3(0.0f, 0.0f, 0.0f);
	particleScaleRange = glm::vec2(1.0f, 1.0f);
	particleCameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	billboardParticles = false;

	//Optional renderables
	particleMesh = NUM_MESHES; //Essentially treated as NULL
	particleTexture = NUM_TEXTURES; //Essentially treated as NULL

	//Initialize the particle array with the new values
	initParticles();
}

ParticleEmitter::~ParticleEmitter()
{
	particles.clear();
}

/* --- Emitter Setters --- */
void ParticleEmitter::setParticleLimit(int newMax)
{
	particles.clear();
	numParticles = newMax;
	initParticles();
}

void ParticleEmitter::setEmitterPosition(glm::vec3 newEmitterPosition) {
	emitterPosition = newEmitterPosition;
}

void ParticleEmitter::setEmitterPosition(float x, float y, float z) {
	emitterPosition = glm::vec3(x, y, z);
}

void ParticleEmitter::setActive(bool _active) {
	active = _active;
}

void ParticleEmitter::setContinuous(bool _continuous) {
	continuous = _continuous;
}

/* --- Particle Attribute Setters --- */
void ParticleEmitter::setParticleLifeRange(float minLife, float maxLife) {
	particleLifeRange = glm::vec2(minLife, maxLife);
}

void ParticleEmitter::setParticleVelRange(glm::vec3 minVelocity, glm::vec3 maxVelocity)
{
	particleVel_Min = minVelocity;
	particleVel_Max = maxVelocity;
}

void ParticleEmitter::setParticleColourRange(glm::vec4 minColour, glm::vec4 maxColour)
{
	particleColour_Min = minColour;
	particleColour_Max = maxColour;
}

void ParticleEmitter::setParticleRotationRange(glm::vec3 minRotation, glm::vec3 maxRotation)
{
	particleRotation_Min = minRotation;
	particleRotation_Max = maxRotation;
}

void ParticleEmitter::setParticleScaleRange(float scaleMin, float scaleMax) {
	particleScaleRange = glm::vec2(scaleMin, scaleMax);
}

void ParticleEmitter::setParticleCameraPosition(glm::vec3 cameraPosition) {
	particleCameraPosition = cameraPosition;
}

void ParticleEmitter::setBillboard(bool billboard) {
	billboardParticles = billboard;
}

void ParticleEmitter::setParticleMesh(MESH_NAME newMesh) {
	particleMesh = newMesh;
}

void ParticleEmitter::setParticleTexture(TEXTURE_NAME texture) {
	particleTexture = texture;
}

void ParticleEmitter::setParticles(float minLife, float maxLife, glm::vec3 minVel, glm::vec3 maxVel, glm::vec4 minColour, glm::vec4 maxColour)
{
	particleLifeRange = glm::vec2(minLife, maxLife);
	particleVel_Min = minVel;
	particleVel_Max = maxVel;
	particleColour_Min = minColour;
	particleColour_Max = maxColour;
}

void ParticleEmitter::setParticles(float minLife, float maxLife, glm::vec3 minVel, glm::vec3 maxVel, glm::vec4 minColour, glm::vec4 maxColour, MESH_NAME mesh, TEXTURE_NAME texture)
{
	particleLifeRange = glm::vec2(minLife, maxLife);
	particleVel_Min = minVel;
	particleVel_Max = maxVel;
	particleColour_Min = minColour;
	particleColour_Max = maxColour;
	particleMesh = mesh;
	particleTexture = texture;
}

/* --- Getters --- */
glm::vec3 ParticleEmitter::getEmitterPosition() const {
	return emitterPosition;
}

int ParticleEmitter::getMaxNumParticles() const {
	return numParticles;
}

bool ParticleEmitter::getActive() const {
	return active;
}

bool ParticleEmitter::getContinuous() const {
	return continuous;
}

/* --- Interactive functions --- */
void ParticleEmitter::applyForceToParticles(glm::vec3 impulseForce)
{
	for (unsigned int i = 0; i < particles.size(); i++)
		particles[i].addImpulse(impulseForce);
}

void ParticleEmitter::update(float deltaTime)
{
	if (particleTexture != NUM_TEXTURES)
		glBindTexture(GL_TEXTURE_2D, AM::assets()->getTexture2D(particleTexture).getTextureID());

	if (active)
	{
		for (unsigned int i = 0; i < particles.size(); i++)
		{
			particles[i].parentEmitterPosition = emitterPosition;

			if (particles[i].timeAlive > particles[i].maxLifetime)
			{
				if (continuous)
					resetParticle(i);
				else
				{
					particles.erase(particles.begin() + i);
					i--;
				}
			}

			particles[i].update(deltaTime);
			particles[i].draw();
		}

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

//Works the same as init except edits the particles that are already there, as opposed to creating new ones
void ParticleEmitter::applyParticleValues()
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		//Position
		particles[i].parentEmitterPosition = emitterPosition;
		particles[i].setPosition(particles[i].parentEmitterPosition);

		//Lifetime
		particles[i].maxLifetime = MathHelper::randomFloat(particleLifeRange.x, particleLifeRange.y);

		//Velocity
		particles[i].setVelocity(MathHelper::randomFloat(particleVel_Min.x, particleVel_Max.x), MathHelper::randomFloat(particleVel_Min.y, particleVel_Max.y), MathHelper::randomFloat(particleVel_Min.z, particleVel_Max.z));

		//Colour
		particles[i].setColour(glm::vec4(MathHelper::randomFloat(particleColour_Min.x, particleColour_Max.x), MathHelper::randomFloat(particleColour_Min.y, particleColour_Max.y), MathHelper::randomFloat(particleColour_Min.z, particleColour_Max.z), MathHelper::randomFloat(particleColour_Min.w, particleColour_Max.w)));

		//Rotation
		particles[i].setRotation(glm::vec3(MathHelper::randomFloat(particleRotation_Min.x, particleRotation_Max.x), MathHelper::randomFloat(particleRotation_Min.y, particleRotation_Max.y), MathHelper::randomFloat(particleRotation_Min.z, particleRotation_Max.z)));
		
		//Scale
		float pScale = MathHelper::randomFloat(particleScaleRange.x, particleScaleRange.y);
		particles[i].setScale(glm::vec3(pScale, pScale, pScale));

		//Billboarding
		particles[i].cameraPosition = particleCameraPosition;
		particles[i].billboard = billboardParticles;

		//Mesh
		if (particleMesh != NUM_MESHES)
			particles[i].setMesh(particleMesh);

		//Texture
		if (particleTexture != NUM_TEXTURES)
			particles[i].setTexture(particleTexture);
	}
}

/* --- Utility functions --- */
void ParticleEmitter::initParticles()
{
	//Reserve data for more efficient loading of vector
	particles.reserve(numParticles);

	//Create the particles
	for (unsigned int i = 0; i < numParticles; i++)
	{
		Particle p;
		
		//Position
		p.parentEmitterPosition = emitterPosition;
		p.setPosition(p.parentEmitterPosition);
		
		//Lifetime
		p.maxLifetime = MathHelper::randomFloat(particleLifeRange.x, particleLifeRange.y);

		//Velocity
		p.setVelocity(MathHelper::randomFloat(particleVel_Min.x, particleVel_Max.x), MathHelper::randomFloat(particleVel_Min.y, particleVel_Max.y), MathHelper::randomFloat(particleVel_Min.z, particleVel_Max.z));

		//Colour
		p.setColour(glm::vec4(MathHelper::randomFloat(particleColour_Min.x, particleColour_Max.x), MathHelper::randomFloat(particleColour_Min.y, particleColour_Max.y), MathHelper::randomFloat(particleColour_Min.z, particleColour_Max.z), MathHelper::randomFloat(particleColour_Min.w, particleColour_Max.w)));

		//Mesh
		if (particleMesh != NUM_MESHES)
			p.setMesh(particleMesh);

		//Texture
		if (particleTexture != NUM_TEXTURES)
			p.setTexture(particleTexture);

		particles.push_back(p);
	}
}

void ParticleEmitter::resetParticle(int i)
{
	//Position
	particles[i].setPosition(particles[i].parentEmitterPosition);

	//Lifetime
	particles[i].timeAlive = 0;
	particles[i].maxLifetime = MathHelper::randomFloat(particleLifeRange.x, particleLifeRange.y);

	//Velocity
	particles[i].setVelocity(MathHelper::randomFloat(particleVel_Min.x, particleVel_Max.x), MathHelper::randomFloat(particleVel_Min.y, particleVel_Max.y), MathHelper::randomFloat(particleVel_Min.z, particleVel_Max.z));

	//Colour
	particles[i].setColour(glm::vec4(MathHelper::randomFloat(particleColour_Min.x, particleColour_Max.x), MathHelper::randomFloat(particleColour_Min.y, particleColour_Max.y), MathHelper::randomFloat(particleColour_Min.z, particleColour_Max.z), MathHelper::randomFloat(particleColour_Min.w, particleColour_Max.w)));
}

/* ===================================== Particle Emitter Class ======================================== */