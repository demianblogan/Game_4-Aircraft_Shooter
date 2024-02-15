#pragma once

#include <deque>

#include <SFML/Graphics/VertexArray.hpp>

#include "SceneNode.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../World/Particle.h"

// ParticleNode class implements a particle in the game scene
// (like smoke, fire, etc.). You can Familiarize with particles data
// in "DataTables.h" file (find ParticleData struct).
class ParticleNode : public SceneNode
{
public:
	ParticleNode(Particle::Type type, const TextureHolder& textureHolder);

	void AddParticle(const sf::Vector2f& position);
	Particle::Type GetParticleType() const;
	virtual unsigned int GetCategory() const override;

private:
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue) override;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void AddVertex(float worldX, float worldY, float textureX, float textureY, const sf::Color& color) const;
	void ComputeVertices() const;

	std::deque<Particle> particles;
	const sf::Texture& texture;
	Particle::Type type;

	mutable sf::VertexArray vertexArray;
	mutable bool needForVertexUpdate = true;
};