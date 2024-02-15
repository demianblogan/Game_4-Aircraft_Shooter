#include "Aircraft.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "DataTables.h"
#include "Pickup.h"
#include "Projectile.h"
#include "../Commands/Command.h"
#include "../Commands/CommandQueue.h"
#include "../Utilities/Utilities.h"
#include "../Utilities/Random.h"
#include "../SceneNodes/Category.h"
#include "../SceneNodes/SoundNode.h"

namespace
{
	const std::vector<AircraftData> AircraftDataTable = InitializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textureHolder, const FontHolder& fontHolder)
	: Entity(AircraftDataTable[int(type)].hitPoints)
	, type(type)
	, sprite(textureHolder.Get(AircraftDataTable[int(type)].textureID), AircraftDataTable[int(type)].textureRectangle)
	, explosionAnimation(textureHolder.Get(Texture::ID::Explosion))
{
	explosionAnimation.SetFrameSize(sf::Vector2i(256, 256));
	explosionAnimation.SetNumberOfFrames(16);
	explosionAnimation.SetDuration(sf::seconds(1));

	CenterOrigin(sprite);
	CenterOrigin(explosionAnimation);

	fireCommand.category = Category::SceneAirLayer;
	fireCommand.action =
		[this, &textureHolder](SceneNode& node, sf::Time)
		{
			CreateBullets(node, textureHolder);
		};

	missileCommand.category = Category::SceneAirLayer;
	missileCommand.action =
		[this, &textureHolder](SceneNode& node, sf::Time)
		{
			CreateProjectile(node, Projectile::Type::Missile, 0, 0.5f, textureHolder);
		};

	dropPickupCommand.category = Category::SceneAirLayer;
	dropPickupCommand.action =
		[this, &textureHolder](SceneNode& node, sf::Time)
		{
			CreatePickup(node, textureHolder);
		};

	auto healthDisplayPtr = std::make_unique<TextNode>(fontHolder, "");
	healthDisplay = healthDisplayPtr.get();
	AttachChild(std::move(healthDisplayPtr));

	if (GetCategory() == Category::PlayerAircraft)
	{
		auto missileDisplayPtr = std::make_unique<TextNode>(fontHolder, "");
		missileDisplayPtr->setPosition(0, 70);
		missileDisplay = missileDisplayPtr.get();
		AttachChild(std::move(missileDisplayPtr));
	}

	UpdateTexts();
}

unsigned int Aircraft::GetCategory() const
{
	return IsAllied() ? Category::PlayerAircraft : Category::EnemyAircraft;
}

sf::FloatRect Aircraft::GetBoundingRectangle() const
{
	return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

bool Aircraft::IsMarkedForRemoval() const
{
	return IsDestroyed() && (explosionAnimation.IsFinished() || !needToShowExplosion);
}

void Aircraft::Remove()
{
	Entity::Remove();
	needToShowExplosion = false;
}

bool Aircraft::IsAllied() const
{
	return type == Type::Eagle;
}

float Aircraft::GetMoveSpeed() const
{
	return AircraftDataTable[int(type)].moveSpeed;
}

void Aircraft::IncreaseFireRate()
{
	if (fireRateLevel < 10)
		fireRateLevel++;
}

void Aircraft::IncreaseSpread()
{
	if (spreadLevel < 3)
		spreadLevel++;
}

void Aircraft::CollectMissiles(unsigned int count)
{
	missileAmmo += count;
}

void Aircraft::Fire()
{
	// Only ships with fire interval != 0 are able to fire.
	if (AircraftDataTable[int(type)].fireInterval != sf::Time::Zero)
		isFiring = true;
}

void Aircraft::LaunchMissile()
{
	if (missileAmmo > 0)
	{
		isLaunchingMissile = true;
		missileAmmo--;
	}
}

void Aircraft::PlayLocalSound(CommandQueue& commandQueue, SoundEffect::ID effect) const
{
	sf::Vector2f worldPosition = GetWorldPosition();

	Command command;
	command.category = Category::SoundEffect;
	command.action = GetDerivedAction<SoundNode>(
		[effect, worldPosition](SoundNode& node, sf::Time)
		{
			node.PlaySound(effect, worldPosition);
		});

	commandQueue.Push(command);
}

void Aircraft::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (IsDestroyed() && needToShowExplosion)
		target.draw(explosionAnimation, states);
	else
		target.draw(sprite, states);
}

void Aircraft::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{
	UpdateTexts();
	UpdateRollAnimation();

	// When entity has been destroyed, is possibly can drop pickup, also we mark it for removal:
	if (IsDestroyed())
	{
		CheckPickupDrop(commandQueue);
		explosionAnimation.Update(deltaTime);

		// Play explosion sound only once:
		if (!isExplosionSoundPlayed)
		{
			SoundEffect::ID soundEffect = Random::GenerateInt(0, 1) == 0 ? SoundEffect::ID::Explosion1 : SoundEffect::ID::Explosion2;
			PlayLocalSound(commandQueue, soundEffect);
			isExplosionSoundPlayed = true;
		}

		return;
	}

	// Check if bullets or missiles are fired:
	CheckProjectileLaunch(deltaTime, commandQueue);

	// Update enemy movement pattern, and apply velocity:
	UpdateMovementPattern(deltaTime);
	Entity::UpdateCurrent(deltaTime, commandQueue);
}

void Aircraft::UpdateMovementPattern(sf::Time deltaTime)
{
	// Enemy airplanes have movement pattern.
	const std::vector<Direction>& directions = AircraftDataTable[int(type)].directions;
	if (!directions.empty())
	{
		float neededDistanceToTravel = directions[directionIndex].distance;

		if (travelledDistance > neededDistanceToTravel)
		{
			directionIndex = (directionIndex + 1) % directions.size();
			travelledDistance = 0;
		}

		// Compute velocity from direction:
		float angleInDegrees = directions[directionIndex].angle + 90.0f;
		float angleInRadians = ConvertDegreesToRadians(angleInDegrees);
		float x = GetMoveSpeed() * std::cos(angleInRadians);
		float y = GetMoveSpeed() * std::sin(angleInRadians);

		SetVelocity(x, y);
		travelledDistance += GetMoveSpeed() * deltaTime.asSeconds();
	}
}

void Aircraft::CheckPickupDrop(CommandQueue& commandQueue)
{
	// There is a 33% change of enemy aircraft drops a pickup after being destroyed: 
	if (!IsAllied() && Random::GenerateInt(0, 2) == 0 && !spawnedPickup)
		commandQueue.Push(dropPickupCommand);

	spawnedPickup = true;
}

void Aircraft::CheckProjectileLaunch(sf::Time deltaTime, CommandQueue& commandQueue)
{
	// Enemies try to fire all the time:
	if (!IsAllied())
		Fire();

	// Check for automatic gunfire, allow only in intervals:
	if (isFiring && fireCountdown <= sf::Time::Zero)
	{
		// Interval expired, we can fire a new bullet:
		commandQueue.Push(fireCommand);
		PlayLocalSound(commandQueue, IsAllied() ? SoundEffect::ID::AlliedGunFire : SoundEffect::ID::EnemyGunFire);

		fireCountdown += AircraftDataTable[int(type)].fireInterval / (fireRateLevel + 1.0f);
		isFiring = false;
	}
	else if (fireCountdown > sf::Time::Zero)
	{
		// Interval not expired, Decrease it further:
		fireCountdown -= deltaTime;
		isFiring = false;
	}

	// Check for missile launch
	if (isLaunchingMissile)
	{
		commandQueue.Push(missileCommand);
		PlayLocalSound(commandQueue, SoundEffect::ID::LaunchMissile);

		isLaunchingMissile = false;
	}
}

void Aircraft::CreateBullets(SceneNode& node, const TextureHolder& textureHolder) const
{
	Projectile::Type type = IsAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;

	switch (spreadLevel)
	{
	case 1:
		CreateProjectile(node, type, 0, 0.5f, textureHolder);
		break;

	case 2:
		CreateProjectile(node, type, -0.33f, 0.33f, textureHolder);
		CreateProjectile(node, type, 0.33f, 0.33f, textureHolder);
		break;

	case 3:
		CreateProjectile(node, type, -0.5f, 0.33f, textureHolder);
		CreateProjectile(node, type, 0, 0.5f, textureHolder);
		CreateProjectile(node, type, +0.5f, 0.33f, textureHolder);
		break;
	}
}

void Aircraft::CreateProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textureHolder) const
{
	auto projectilePtr = std::make_unique<Projectile>(type, textureHolder);

	sf::Vector2f offset(xOffset * sprite.getGlobalBounds().width, yOffset * sprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectilePtr->GetMoveSpeed());

	float sign = IsAllied() ? -1.0f : 1.0f;
	projectilePtr->setPosition(GetWorldPosition() + offset * sign);
	projectilePtr->SetVelocity(velocity * sign);
	node.AttachChild(std::move(projectilePtr));
}

void Aircraft::CreatePickup(SceneNode& node, const TextureHolder& textureHolder) const
{
	int pickupTypeIndex = Random::GenerateInt(0, int(Pickup::Type::Count) - 1);
	Pickup::Type type = Pickup::Type(pickupTypeIndex);

	auto pickupPtr = std::make_unique<Pickup>(type, textureHolder);
	pickupPtr->setPosition(GetWorldPosition());
	pickupPtr->SetVelocity(0, 1);
	node.AttachChild(std::move(pickupPtr));
}

void Aircraft::UpdateTexts()
{
	if (IsDestroyed())
		healthDisplay->SetString("");
	else
		healthDisplay->SetString(std::to_string(GetHitPoints()) + " HP");

	healthDisplay->setPosition(0, 50);
	healthDisplay->setRotation(-getRotation());

	if (missileDisplay != nullptr)
	{
		if (missileAmmo == 0 || IsDestroyed())
			missileDisplay->SetString("");
		else
			missileDisplay->SetString("M: " + std::to_string(missileAmmo));
	}
}

void Aircraft::UpdateRollAnimation()
{
	if (AircraftDataTable[int(type)].hasRollAnimation)
	{
		sf::IntRect textureRectangle = AircraftDataTable[int(type)].textureRectangle;

		if (GetVelocity().x < 0)
			textureRectangle.left += textureRectangle.width;
		else if (GetVelocity().x > 0)
			textureRectangle.left += textureRectangle.width * 2;

		sprite.setTextureRect(textureRectangle);
	}
}