#include "Aircraft.h"
#include "DataTables.h"
#include "Particle.h"
#include "Pickup.h"
#include "Projectile.h"

using namespace std::placeholders;

std::vector<AircraftData> InitializeAircraftData()
{
	int aircraftCount = int(Aircraft::Type::Count);
	std::vector<AircraftData> data(aircraftCount);

	data[int(Aircraft::Type::Eagle)].hitPoints = 100;
	data[int(Aircraft::Type::Eagle)].moveSpeed = 200;
	data[int(Aircraft::Type::Eagle)].fireInterval = sf::seconds(1);
	data[int(Aircraft::Type::Eagle)].textureID = Texture::ID::Entities;
	data[int(Aircraft::Type::Eagle)].textureRectangle = sf::IntRect(0, 0, 48, 64);
	data[int(Aircraft::Type::Eagle)].hasRollAnimation = true;

	data[int(Aircraft::Type::Raptor)].hitPoints = 20;
	data[int(Aircraft::Type::Raptor)].moveSpeed = 80;
	data[int(Aircraft::Type::Raptor)].textureID = Texture::ID::Entities;
	data[int(Aircraft::Type::Raptor)].textureRectangle = sf::IntRect(144, 0, 84, 64);
	data[int(Aircraft::Type::Raptor)].directions.push_back(Direction(45, 80));
	data[int(Aircraft::Type::Raptor)].directions.push_back(Direction(-45, 160));
	data[int(Aircraft::Type::Raptor)].directions.push_back(Direction(45, 80));
	data[int(Aircraft::Type::Raptor)].fireInterval = sf::Time::Zero;
	data[int(Aircraft::Type::Raptor)].hasRollAnimation = false;

	data[int(Aircraft::Type::Avenger)].hitPoints = 40;
	data[int(Aircraft::Type::Avenger)].moveSpeed = 50;
	data[int(Aircraft::Type::Avenger)].textureID = Texture::ID::Entities;
	data[int(Aircraft::Type::Avenger)].textureRectangle = sf::IntRect(228, 0, 60, 59);
	data[int(Aircraft::Type::Avenger)].directions.push_back(Direction(45, 50));
	data[int(Aircraft::Type::Avenger)].directions.push_back(Direction(0, 50));
	data[int(Aircraft::Type::Avenger)].directions.push_back(Direction(-45, 100));
	data[int(Aircraft::Type::Avenger)].directions.push_back(Direction(0, 50));
	data[int(Aircraft::Type::Avenger)].directions.push_back(Direction(45, 50));
	data[int(Aircraft::Type::Avenger)].fireInterval = sf::seconds(2);
	data[int(Aircraft::Type::Avenger)].hasRollAnimation = false;

	return data;
}

std::vector<ProjectileData> InitializeProjectileData()
{
	int projectileCount = int(Projectile::Type::Count);
	std::vector<ProjectileData> data(projectileCount);

	data[int(Projectile::Type::AlliedBullet)].damage = 10;
	data[int(Projectile::Type::AlliedBullet)].moveSpeed = 300;
	data[int(Projectile::Type::AlliedBullet)].textureID = Texture::ID::Entities;
	data[int(Projectile::Type::AlliedBullet)].textureRectangle = sf::IntRect(175, 64, 3, 14);

	data[int(Projectile::Type::EnemyBullet)].damage = 10;
	data[int(Projectile::Type::EnemyBullet)].moveSpeed = 300;
	data[int(Projectile::Type::EnemyBullet)].textureID = Texture::ID::Entities;
	data[int(Projectile::Type::EnemyBullet)].textureRectangle = sf::IntRect(178, 64, 3, 14);

	data[int(Projectile::Type::Missile)].damage = 200;
	data[int(Projectile::Type::Missile)].moveSpeed = 150;
	data[int(Projectile::Type::Missile)].textureID = Texture::ID::Entities;
	data[int(Projectile::Type::Missile)].textureRectangle = sf::IntRect(160, 64, 15, 32);

	return data;
}

std::vector<PickupData> InitializePickupData()
{
	int pickupCount = int(Pickup::Type::Count);
	std::vector<PickupData> data(pickupCount);

	data[int(Pickup::Type::HealthRefill)].textureID = Texture::ID::Entities;
	data[int(Pickup::Type::HealthRefill)].textureRectangle = sf::IntRect(0, 64, 40, 40);
	data[int(Pickup::Type::HealthRefill)].action = std::bind(&Aircraft::Repair, _1, 25);

	data[int(Pickup::Type::MissileRefill)].textureID = Texture::ID::Entities;
	data[int(Pickup::Type::MissileRefill)].textureRectangle = sf::IntRect(40, 64, 40, 40);
	data[int(Pickup::Type::MissileRefill)].action = std::bind(&Aircraft::CollectMissiles, _1, 3);

	data[int(Pickup::Type::FireSpread)].textureID = Texture::ID::Entities;
	data[int(Pickup::Type::FireSpread)].textureRectangle = sf::IntRect(80, 64, 40, 40);
	data[int(Pickup::Type::FireSpread)].action = std::bind(&Aircraft::IncreaseSpread, _1);

	data[int(Pickup::Type::FireRate)].textureID = Texture::ID::Entities;
	data[int(Pickup::Type::FireRate)].textureRectangle = sf::IntRect(120, 64, 40, 40);
	data[int(Pickup::Type::FireRate)].action = std::bind(&Aircraft::IncreaseFireRate, _1);

	return data;
}

std::vector<ParticleData> InitializeParticleData()
{
	int particleCount = int(Pickup::Type::Count);
	std::vector<ParticleData> data(particleCount);

	data[int(Particle::Type::Propellant)].color = sf::Color(255, 255, 50);
	data[int(Particle::Type::Propellant)].lifetime = sf::seconds(0.6f);

	data[int(Particle::Type::Smoke)].color = sf::Color(50, 50, 50);
	data[int(Particle::Type::Smoke)].lifetime = sf::seconds(4);

	return data;
}