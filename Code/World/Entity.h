#pragma once

#include <SFML/System/Vector2.hpp> 
#include "../SceneNodes/SceneNode.h"
#include "../Commands/CommandQueue.h"

// Game State has a "World" object. World contains of entites.
// Every object in the world is an entity: it has its velocity
// and hit points (player, enemies, pickups, bullets, ...).
// So it a base class for all entities in the world.
class Entity : public SceneNode
{
public:
	explicit Entity(int hitPoints);

	void SetVelocity(const sf::Vector2f& velocity);
	void SetVelocity(float x, float y);
	const sf::Vector2f& GetVelocity() const;

	void Accelerate(const sf::Vector2f& velocity);
	void Accelerate(float x, float y);

	int GetHitPoints() const;
	void Repair(int points);
	void Damage(int points);
	void Destroy();
	virtual void Remove();
	virtual bool IsDestroyed() const;

protected:
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue) override;

private:

	sf::Vector2f velocity;
	int hitPoints;
};