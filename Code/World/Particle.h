#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

// Particle is a simple entity of the world, but it doesn't
// have velocity and hit points, that's why it's not inherited from
// "Entity" class.
struct Particle
{
	enum class Type
	{
		Propellant,
		Smoke,
		Count
	};

	sf::Vector2f position;
	sf::Color color;
	sf::Time lifetime;
};