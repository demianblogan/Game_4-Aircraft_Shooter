#pragma once

#include <functional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include "../ResourceManagement/ResourceHolder.h"
#include "../ResourceManagement/ResourceIdentifiers.h"

class Aircraft;

struct Direction
{
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{ }

	float angle;
	float distance;
};

struct AircraftData
{
	int hitPoints;
	float moveSpeed;
	Texture::ID textureID;
	sf::IntRect textureRectangle;
	sf::Time fireInterval;
	std::vector<Direction> directions;
	bool hasRollAnimation;
};

struct ProjectileData
{
	int damage;
	float moveSpeed;
	Texture::ID textureID;
	sf::IntRect textureRectangle;
};

struct PickupData
{
	std::function<void(Aircraft&)> action;
	Texture::ID textureID;
	sf::IntRect textureRectangle;
};

struct ParticleData
{
	sf::Color color;
	sf::Time lifetime;
};

std::vector<AircraftData> InitializeAircraftData();
std::vector<ProjectileData> InitializeProjectileData();
std::vector<PickupData> InitializePickupData();
std::vector<ParticleData> InitializeParticleData();