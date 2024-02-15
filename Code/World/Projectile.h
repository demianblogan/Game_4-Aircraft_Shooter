#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"

// Projectile is a bullet or missile that can be launched by enemies' ships or player's ship.
// Is it's a missile, i can be guided towards a target (only player can launch them).
class Projectile : public Entity
{
public:
	enum class Type
	{
		AlliedBullet,
		EnemyBullet,
		Missile,
		Count
	};

	Projectile(Type type, const TextureHolder& textureHolder);

	void GuideTowards(sf::Vector2f position);
	bool isGuided() const;

	virtual unsigned int GetCategory() const override;
	virtual sf::FloatRect GetBoundingRectangle() const override;
	float GetMoveSpeed() const;
	int GetDamage() const;

private:
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue) override;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	Type type;
	sf::Sprite sprite;
	sf::Vector2f targetDirection;
};