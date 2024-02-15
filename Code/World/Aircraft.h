#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "Projectile.h"
#include "../Animation/Animation.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "../SceneNodes/TextNode.h"

class CommandQueue;

// Aircraft is an entity that can be controlled by the player,
// or enemy. Game has two enemy aircrafts. Every aircraft can shoot
// bullets or missiles (only player can shoot missiles). Every aircraft
// has its own fire rate, texture, hit points, and velocity. Also
// every aircraft after its death can spawn a pickup.
class Aircraft : public Entity
{
public:
	enum class Type
	{
		Eagle,
		Raptor,
		Avenger,
		Count
	};

	explicit Aircraft(Type type, const TextureHolder& textureHolder, const FontHolder& fontHolder);

	virtual unsigned int GetCategory() const override;
	virtual sf::FloatRect GetBoundingRectangle() const override;
	virtual bool IsMarkedForRemoval() const override;
	virtual void Remove() override;
	bool IsAllied() const;
	float GetMoveSpeed() const;

	void IncreaseFireRate();
	void IncreaseSpread();
	void CollectMissiles(unsigned int count);

	void Fire();
	void LaunchMissile();
	void PlayLocalSound(CommandQueue& commandQueue, SoundEffect::ID effect) const;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue) override;
	void UpdateMovementPattern(sf::Time deltaTime);
	
	void CheckPickupDrop(CommandQueue& commandQueue);
	void CheckProjectileLaunch(sf::Time deltaTime, CommandQueue& commandQueue);

	void CreateBullets(SceneNode& node, const TextureHolder& textureHolder) const;
	void CreateProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textureHolder) const;
	void CreatePickup(SceneNode& node, const TextureHolder& textureHolder) const;

	void UpdateTexts();
	void UpdateRollAnimation();

	Type type;
	sf::Sprite sprite;	
	Command fireCommand;
	Command missileCommand;
	Animation explosionAnimation;
	sf::Time fireCountdown = sf::Time::Zero;
	bool isFiring = false;
	bool isLaunchingMissile = false;
	bool needToShowExplosion = true;
	bool isExplosionSoundPlayed = false;
	bool spawnedPickup = false;

	int fireRateLevel = 1;
	int spreadLevel = 1;
	int missileAmmo = 2;

	Command dropPickupCommand;
	float travelledDistance = 0;
	int directionIndex = 0;
	TextNode* healthDisplay = nullptr;
	TextNode* missileDisplay = nullptr;
};