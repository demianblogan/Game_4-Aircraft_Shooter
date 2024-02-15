#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "../ResourceManagement/ResourceIdentifiers.h"

class Aircraft;

// Pickup in an entity that player can collect to gain some bonuses.
// It's spawned right after enemy aircraft is exploded. Pickup can only
// be applied to a player.
class Pickup : public Entity
{
public:
	enum class Type
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		Count
	};

	Pickup(Type type, const TextureHolder& textureHolder);

	virtual unsigned int GetCategory() const override;
	virtual sf::FloatRect GetBoundingRectangle() const override;
	
	void Apply(Aircraft& player) const;

protected:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Type type;
	sf::Sprite sprite;
};