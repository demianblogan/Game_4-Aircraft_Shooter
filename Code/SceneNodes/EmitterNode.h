#pragma once

#include "SceneNode.h"
#include "../World/Particle.h"

class ParticleNode;

// Emitter is an object that "emits" particles of specific type. 
class EmitterNode : public SceneNode
{
public:
	explicit EmitterNode(Particle::Type type);

private:
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue) override;
	void EmitParticles(sf::Time deltaTime);

	sf::Time accumulatedTime = sf::Time::Zero;
	Particle::Type type;
	ParticleNode* particleSystem = nullptr;
};