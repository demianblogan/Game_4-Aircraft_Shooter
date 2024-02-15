#pragma once

#include <memory>
#include <set>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "Category.h"
#include "../Commands/Command.h"

struct Command;
class CommandQueue;

// All game entities are nodes of the scene graph, which is displayed in the window. 
// Every frame the game goes through this graph, working with each of its nodes.
// Each node can have other child nodes within it (for example, the player's ship
// can have an accompanying fleet of other ships that will move in the same way).
// During each frame of the game, the game updates each node. Each node can have
// a collision with another node. And each node can be drawn on the window.

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	using NodePointer = std::unique_ptr<SceneNode>;
	using Pair = std::pair<SceneNode*, SceneNode*>;

	explicit SceneNode(Category::Type category = Category::None);

	void AttachChild(NodePointer child);
	NodePointer DetachChild(const SceneNode& node);

	void OnCommand(const Command& command, sf::Time deltaTime);

	void Update(sf::Time deltaTime, CommandQueue& commandQueue);

	sf::Transform GetWorldTransform() const;
	const sf::Vector2f GetWorldPosition() const;

	virtual unsigned int GetCategory() const;

	virtual sf::FloatRect GetBoundingRectangle() const;
	virtual bool IsMarkedForRemoval() const;
	virtual bool IsDestroyed() const;

	void RemoveWrecks();

	void CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void CheckNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

private:
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void UpdateChildren(sf::Time deltaTime, CommandQueue& commandQueue);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<NodePointer> children;
	SceneNode* parent = nullptr;
	Category::Type defaultCategory;
};

bool AreNodesCollided(const SceneNode& left, const SceneNode& right);
float GetDistance(const SceneNode& left, const SceneNode& right);