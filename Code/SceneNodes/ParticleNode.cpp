#include "ParticleNode.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../World/DataTables.h"

namespace
{
    const std::vector<ParticleData> ParticleTable = InitializeParticleData();
}

ParticleNode::ParticleNode(Particle::Type type, const TextureHolder& textureHolder)
    : texture(textureHolder.Get(Texture::ID::Particle))
    , type(type)
    , vertexArray(sf::Quads)
{ }

void ParticleNode::AddParticle(const sf::Vector2f& position)
{
    Particle particle;
    particle.position = position;
    particle.color = ParticleTable[int(type)].color;
    particle.lifetime = ParticleTable[int(type)].lifetime;

    particles.push_back(particle);
}

Particle::Type ParticleNode::GetParticleType() const
{
    return type;
}

unsigned int ParticleNode::GetCategory() const
{
    return Category::ParticleSystem;
}

void ParticleNode::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{
    // Remove expired particles at beginning:
    while (!particles.empty() && particles.front().lifetime <= sf::Time::Zero)
        particles.pop_front();

    // Decrease lifetime of existing particles:
    for (Particle& particle : particles)
        particle.lifetime -= deltaTime;

    needForVertexUpdate = true;
}

void ParticleNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (needForVertexUpdate)
    {
        ComputeVertices();
        needForVertexUpdate = false;
    }

    states.texture = &texture;
    target.draw(vertexArray, states);
}

void ParticleNode::AddVertex(float worldX, float worldY, float textureX, float textureY, const sf::Color& color) const
{
    sf::Vertex vertex;
    vertex.position = sf::Vector2f(worldX, worldY);
    vertex.texCoords = sf::Vector2f(textureX, textureY);
    vertex.color = color;

    vertexArray.append(vertex);
}

void ParticleNode::ComputeVertices() const
{
    sf::Vector2f size(texture.getSize());
    sf::Vector2f halfSize = size / 2.0f;

    // Refill vertex array:
    vertexArray.clear();

    for (const Particle& particle : particles)
    {
        sf::Vector2f position = particle.position;
        sf::Color color = particle.color;

        float ratio = particle.lifetime.asSeconds() / ParticleTable[int(type)].lifetime.asSeconds(); // [-value...1]
        color.a = static_cast<sf::Uint8>(255 * std::max(0.0f, ratio)); // [0...255]

        AddVertex(position.x - halfSize.x, position.y - halfSize.y, 0, 0, color);
        AddVertex(position.x + halfSize.x, position.y - halfSize.y, size.x, 0, color);
        AddVertex(position.x + halfSize.x, position.y + halfSize.y, size.x, size.y, color);
        AddVertex(position.x - halfSize.x, position.y + halfSize.y, 0, size.y, color);
    }
}