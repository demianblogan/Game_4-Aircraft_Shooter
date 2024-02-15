#include "Entity.h"
#include <cassert>

Entity::Entity(int hitPoints)
	: hitPoints(hitPoints)
{ }

void Entity::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Entity::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

const sf::Vector2f& Entity::GetVelocity() const
{
	return velocity;
}

void Entity::Accelerate(const sf::Vector2f& velocity)
{
	this->velocity += velocity;
}

void Entity::Accelerate(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

int Entity::GetHitPoints() const
{
	return hitPoints;
}

void Entity::Repair(int points)
{
	assert(points > 0);
	hitPoints += points;
}

void Entity::Damage(int points)
{
	assert(points > 0);
	hitPoints -= points;
}

void Entity::Destroy()
{
	hitPoints = 0;
}

void Entity::Remove()
{
	Destroy();
}

bool Entity::IsDestroyed() const
{
	return hitPoints <= 0;
}

void Entity::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{
	move(velocity * deltaTime.asSeconds());
}