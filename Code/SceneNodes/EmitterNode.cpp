#include "EmitterNode.h"

#include "ParticleNode.h"
#include "../Commands/CommandQueue.h"

EmitterNode::EmitterNode(Particle::Type type)
	: type(type)
{ }

void EmitterNode::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{
	if (particleSystem != nullptr)
	{
		EmitParticles(deltaTime);
	}
	else
	{
		// Find particle node with the same type as emitter node:
		auto finder = [this](ParticleNode& node, sf::Time)
			{
				if (node.GetParticleType() == type)
					particleSystem = &node;
			};

		Command command;
		command.category = Category::ParticleSystem;
		command.action = GetDerivedAction<ParticleNode>(finder);

		commandQueue.Push(command);
	}
}

void EmitterNode::EmitParticles(sf::Time deltaTime)
{
	const float EMISSION_RATE = 30;
	const sf::Time INTERVAL = sf::seconds(1) / EMISSION_RATE;

	accumulatedTime += deltaTime;

	while (accumulatedTime > INTERVAL)
	{
		accumulatedTime -= INTERVAL;
		particleSystem->AddParticle(GetWorldPosition());
	}
}