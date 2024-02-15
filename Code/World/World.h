#pragma once

#include <array>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Aircraft.h"
#include "../Audio/SoundPlayer.h"
#include "../Commands/CommandQueue.h"
#include "../Graphics/BloomEffect.h"
#include "../ResourceManagement/ResourceHolder.h"

// World is a class that represents everything in Game State. It contains
// background texture (map), airships, pickups, particles, and projectiles.
// It manipulates all of these entities.
class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window, FontHolder& fontHolder, SoundPlayer& soundPlayer);
	void Update(sf::Time deltaTime);
	void Draw();

	CommandQueue& GetCommandQueue();

	bool HasAlivePlayer() const;
	bool HasPlayerReachedEnd() const;

private:
	// Some sprites must be rendered below others. That's why I added Layer system.
	enum class Layer
	{
		Background,
		LowerAir,
		UpperAir,
		Count
	};

	struct SpawnPoint
	{
		SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type), x(x), y(y)
		{ }

		Aircraft::Type type;
		float x;
		float y;
	};

	void LoadTextures();
	void BuildScene();
	void AddEnemies();
	void AddEnemy(Aircraft::Type type, float x, float y);
	void SpawnEnemies();
	void DestroyEntitiesOutsideView();
	void HandleCollisions();
	void GuideMissiles();
	void UpdateSounds();

	sf::FloatRect GetViewBounds() const;
	sf::FloatRect GetBattlefieldBounds() const;

	sf::RenderWindow& window;
	sf::RenderTexture sceneTexture;
	sf::View worldView;
	TextureHolder textureHolder;
	FontHolder& fontHolder;
	SoundPlayer& soundPlayer;

	SceneNode sceneGraph;
	std::array<SceneNode*, int(Layer::Count)> sceneLayers;
	CommandQueue commandQueue;

	sf::FloatRect worldBounds;
	sf::Vector2f playerSpawnPosition;
	float cameraScrollSpeed = -50;
	Aircraft* playerAircraft = nullptr;

	std::vector<SpawnPoint> enemySpawnPoints;
	std::vector<Aircraft*> activeEnemies;

	BloomEffect bloomEffect;
};