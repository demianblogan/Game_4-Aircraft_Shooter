#include "World.h"

#include <SFML/Graphics/Texture.hpp>

#include "Pickup.h"
#include "Projectile.h"
#include "../SceneNodes/ParticleNode.h"
#include "../SceneNodes/SoundNode.h"
#include "../SceneNodes/SpriteNode.h"

static bool NodesHaveSameCategory(SceneNode::Pair& colliders, Category::Type leftCategory, Category::Type rightCategory)
{
	unsigned int leftNodeCategory = colliders.first->GetCategory();
	unsigned int rightNodeCategory = colliders.second->GetCategory();

	if ((leftNodeCategory & leftCategory) && (rightNodeCategory & rightCategory))
	{
		return true;
	}
	else if ((leftNodeCategory & rightCategory) && (rightNodeCategory & leftCategory))
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

World::World(sf::RenderWindow& window, FontHolder& fontHolder, SoundPlayer& soundPlayer)
	: window(window)
	, worldView(window.getDefaultView())
	, fontHolder(fontHolder)
	, soundPlayer(soundPlayer)
	, worldBounds(0, 0, worldView.getSize().x, 5000)
	, playerSpawnPosition(worldView.getSize().x / 2, worldBounds.height - worldView.getSize().y / 2)
{
	sceneTexture.create(window.getSize().x, window.getSize().y);

	LoadTextures();
	BuildScene();

	worldView.setCenter(playerSpawnPosition);
}

void World::Update(sf::Time deltaTime)
{
	worldView.move(0, cameraScrollSpeed * deltaTime.asSeconds());
	playerAircraft->SetVelocity(0, 0);

	DestroyEntitiesOutsideView();
	GuideMissiles();

	// Forward commands to the scene graph:
	while (!commandQueue.IsEmpty())
		sceneGraph.OnCommand(commandQueue.Pop(), deltaTime);

	// Fix player aircraft's diagonal movement:
	const sf::Vector2f& velocity = playerAircraft->GetVelocity();
	if (velocity.x != 0 && velocity.y != 0)
		playerAircraft->SetVelocity(velocity / std::sqrt(2.0f));

	// Add camera speed to the player's aircraft:
	playerAircraft->Accelerate(0, cameraScrollSpeed);

	HandleCollisions();

	sceneGraph.RemoveWrecks();
	SpawnEnemies();

	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.0f, worldView.getSize());
	const float DISTANCE_FROM_BORDER = 40.0f;

	sf::Vector2f position = playerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + DISTANCE_FROM_BORDER);                    // check left side
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - DISTANCE_FROM_BORDER); // check right side
	position.y = std::max(position.y, viewBounds.top + DISTANCE_FROM_BORDER);                     // check top side
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - DISTANCE_FROM_BORDER); // check bottom side

	playerAircraft->setPosition(position);

	sceneGraph.Update(deltaTime, commandQueue);

	UpdateSounds();
}

void World::Draw()
{
	if (PostEffect::IsSupported())
	{
		sceneTexture.clear();
		sceneTexture.setView(worldView);
		sceneTexture.draw(sceneGraph);
		sceneTexture.display();
		bloomEffect.Apply(sceneTexture, window);
	}
	else
	{
		window.setView(worldView);
		window.draw(sceneGraph);
	}
}

CommandQueue& World::GetCommandQueue()
{
	return commandQueue;
}

bool World::HasAlivePlayer() const
{
	return !playerAircraft->IsMarkedForRemoval();
}

bool World::HasPlayerReachedEnd() const
{
	return !worldBounds.contains(playerAircraft->getPosition());
}

void World::LoadTextures()
{
	textureHolder.Load(Texture::ID::Entities, "Resources/Textures/Entities.png");
	textureHolder.Load(Texture::ID::Jungle, "Resources/Textures/Jungle.png");
	textureHolder.Load(Texture::ID::Explosion, "Resources/Textures/Explosion.png");
	textureHolder.Load(Texture::ID::Particle, "Resources/Textures/Particle.png");
	textureHolder.Load(Texture::ID::FinishLine, "Resources/Textures/FinishLine.png");
}

void World::BuildScene()
{
	for (int i = 0; i < sceneLayers.size(); i++)
	{
		Category::Type category = (i == int(Layer::LowerAir)) ? Category::SceneAirLayer : Category::None;

		auto layerPtr = std::make_unique<SceneNode>(category);
		sceneLayers[i] = layerPtr.get();
		sceneGraph.AttachChild(std::move(layerPtr));
	}

	// Prepare the tiled background:
	sf::Texture& jungleTexture = textureHolder.Get(Texture::ID::Jungle);
	sf::IntRect jungleTextureRectangle(worldBounds);
	jungleTexture.setRepeated(true);

	float viewHeight = worldView.getSize().y;
	jungleTextureRectangle.height += int(viewHeight);

	// Add the background sprite to the scene:
	auto jungleSpritePtr = std::make_unique<SpriteNode>(jungleTexture, jungleTextureRectangle);
	jungleSpritePtr->setPosition(worldBounds.left, worldBounds.top - viewHeight);
	sceneLayers[int(Layer::Background)]->AttachChild(std::move(jungleSpritePtr));

	// Add the finish line to the scene:
	sf::Texture& finishTexture = textureHolder.Get(Texture::ID::FinishLine);
	auto finishSpritePtr = std::make_unique<SpriteNode>(finishTexture);
	finishSpritePtr->setPosition(0, -76);
	sceneLayers[int(Layer::Background)]->AttachChild(std::move(finishSpritePtr));

	// Add particle node to the scene:
	auto smokeNodePtr = std::make_unique<ParticleNode>(Particle::Type::Smoke, textureHolder);
	sceneLayers[int(Layer::LowerAir)]->AttachChild(std::move(smokeNodePtr));

	// Add propellant particle node to the scene:
	auto propellantNodePtr = std::make_unique<ParticleNode>(Particle::Type::Propellant, textureHolder);
	sceneLayers[int(Layer::LowerAir)]->AttachChild(std::move(propellantNodePtr));

	// Add sound effect node:
	auto soundNodePtr = std::make_unique<SoundNode>(soundPlayer);
	sceneGraph.AttachChild(std::move(soundNodePtr));

	// Add player's aircraft:
	auto aircraftPtr = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textureHolder, fontHolder);
	playerAircraft = aircraftPtr.get();
	playerAircraft->setPosition(playerSpawnPosition);
	sceneLayers[int(Layer::UpperAir)]->AttachChild(std::move(aircraftPtr));

	AddEnemies();
}

void World::AddEnemies()
{
	AddEnemy(Aircraft::Type::Raptor,     0.f,  500.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 1000.f);
	AddEnemy(Aircraft::Type::Raptor,   100.f, 1150.f);
	AddEnemy(Aircraft::Type::Raptor,  -100.f, 1150.f);
	AddEnemy(Aircraft::Type::Avenger,   70.f, 1500.f);
	AddEnemy(Aircraft::Type::Avenger,  -70.f, 1500.f);
	AddEnemy(Aircraft::Type::Avenger,  -70.f, 1710.f);
	AddEnemy(Aircraft::Type::Avenger,   70.f, 1700.f);
	AddEnemy(Aircraft::Type::Avenger,   30.f, 1850.f);
	AddEnemy(Aircraft::Type::Raptor,   300.f, 2200.f);
	AddEnemy(Aircraft::Type::Raptor,  -300.f, 2200.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 2200.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 2500.f);
	AddEnemy(Aircraft::Type::Avenger, -300.f, 2700.f);
	AddEnemy(Aircraft::Type::Avenger, -300.f, 2700.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 3000.f);
	AddEnemy(Aircraft::Type::Raptor,   250.f, 3250.f);
	AddEnemy(Aircraft::Type::Raptor,  -250.f, 3250.f);
	AddEnemy(Aircraft::Type::Avenger,    0.f, 3500.f);
	AddEnemy(Aircraft::Type::Avenger,    0.f, 3700.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 3800.f);
	AddEnemy(Aircraft::Type::Avenger,    0.f, 4000.f);
	AddEnemy(Aircraft::Type::Avenger, -200.f, 4200.f);
	AddEnemy(Aircraft::Type::Raptor,   200.f, 4200.f);
	AddEnemy(Aircraft::Type::Raptor,     0.f, 4400.f);

	// Sort all enemies according to their y value,
	// such that lower enemies are checked first for spawning:
	std::sort(enemySpawnPoints.begin(), enemySpawnPoints.end(),
		[](const SpawnPoint& left, const SpawnPoint& right)
		{
			return left.y < right.y;
		});
}

void World::AddEnemy(Aircraft::Type type, float x, float y)
{
	SpawnPoint spawnPoint(type, playerSpawnPosition.x + x, playerSpawnPosition.y - y);
	enemySpawnPoints.push_back(spawnPoint);
}

void World::SpawnEnemies()
{
	// Spawn all enemies entering the view area (including upper extra distance):
	while (!enemySpawnPoints.empty() && enemySpawnPoints.back().y > GetBattlefieldBounds().top)
	{
		SpawnPoint spawnPoint = enemySpawnPoints.back();

		auto enemyPtr = std::make_unique<Aircraft>(spawnPoint.type, textureHolder, fontHolder);
		enemyPtr->setPosition(spawnPoint.x, spawnPoint.y);
		enemyPtr->setRotation(180);

		sceneLayers[int(Layer::UpperAir)]->AttachChild(std::move(enemyPtr));

		enemySpawnPoints.pop_back();
	}
}

void World::DestroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = GetDerivedAction<Entity>(
		[this](Entity& entity, sf::Time)
		{
			if (!GetBattlefieldBounds().intersects(entity.GetBoundingRectangle()))
				entity.Remove();
		}
	);

	commandQueue.Push(command);
}

void World::HandleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.CheckSceneCollision(sceneGraph, collisionPairs);

	for (SceneNode::Pair collisionPair : collisionPairs)
	{
		if (NodesHaveSameCategory(collisionPair, Category::PlayerAircraft, Category::EnemyAircraft))
		{
			Aircraft& player = static_cast<Aircraft&>(*collisionPair.first);
			Aircraft& enemy = static_cast<Aircraft&>(*collisionPair.second);

			player.Damage(enemy.GetHitPoints());
			enemy.Destroy();
		}
		else if (NodesHaveSameCategory(collisionPair, Category::PlayerAircraft, Category::Pickup))
		{
			Aircraft& player = static_cast<Aircraft&>(*collisionPair.first);
			Pickup& pickup = static_cast<Pickup&>(*collisionPair.second);

			pickup.Apply(player);
			pickup.Destroy();
			player.PlayLocalSound(commandQueue, SoundEffect::ID::CollectPickup);
		}
		else if (NodesHaveSameCategory(collisionPair, Category::EnemyAircraft, Category::AlliedProjectile)
			|| NodesHaveSameCategory(collisionPair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
			Aircraft& aircraft = static_cast<Aircraft&>(*collisionPair.first);
			Projectile& projectile = static_cast<Projectile&>(*collisionPair.second);

			aircraft.Damage(projectile.GetDamage());
			projectile.Destroy();
		}
	}
}

void World::GuideMissiles()
{
	// Setup command that stores all enemies in "activeEnemies":
	Command activeEnemiesCollector;
	activeEnemiesCollector.category = Category::EnemyAircraft;
	activeEnemiesCollector.action = GetDerivedAction<Aircraft>(
		[this](Aircraft& enemy, sf::Time)
		{
			if (!enemy.IsDestroyed())
				activeEnemies.push_back(&enemy);
		});

	// Setup command that guides all missiles to the enemy which is currently closest to the player:
	Command missileGuider;
	missileGuider.category = Category::AlliedProjectile;
	missileGuider.action = GetDerivedAction<Projectile>(
		[this](Projectile& missile, sf::Time)
		{
			if (!missile.isGuided())
				return;

			float minDistance = std::numeric_limits<float>::max();
			Aircraft* closestEnemy = nullptr;

			for (Aircraft* enemy : activeEnemies)
			{
				float enemyDistance = GetDistance(missile, *enemy);
				if (enemyDistance < minDistance)
				{
					closestEnemy = enemy;
					minDistance = enemyDistance;
				}
			}

			if (closestEnemy != nullptr)
				missile.GuideTowards(closestEnemy->GetWorldPosition());
		});

	commandQueue.Push(activeEnemiesCollector);
	commandQueue.Push(missileGuider);

	activeEnemies.clear();
}

void World::UpdateSounds()
{
	// Set listener's position to player position:
	soundPlayer.SetListenerPosition(playerAircraft->GetWorldPosition());

	soundPlayer.RemoveStoppedSounds();
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.0f, worldView.getSize());
}

sf::FloatRect World::GetBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = GetViewBounds();
	bounds.top -= 100;
	bounds.height += 100;

	return bounds;
}