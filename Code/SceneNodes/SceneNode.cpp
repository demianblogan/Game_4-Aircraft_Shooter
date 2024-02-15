#include "SceneNode.h"

#include <algorithm>
#include <cassert>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Commands/Command.h"
#include "../Commands/CommandQueue.h"
#include "../Utilities/Utilities.h"

SceneNode::SceneNode(Category::Type category)
	: defaultCategory(category)
{ }

void SceneNode::AttachChild(NodePointer child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::NodePointer SceneNode::DetachChild(const SceneNode& node)
{
	auto searchFunction = [&](NodePointer& pointer) { return pointer.get() == &node; };
	auto foundIterator = std::find_if(children.begin(), children.end(), searchFunction);
	assert(foundIterator != children.end());

	NodePointer detachedChildPointer = std::move(*foundIterator);
	detachedChildPointer->parent = nullptr;
	children.erase(foundIterator);

	return detachedChildPointer;
}

void SceneNode::OnCommand(const Command& command, sf::Time deltaTime)
{
	if (command.category & GetCategory())
		command.action(*this, deltaTime);

	for (const NodePointer& child : children)
		child->OnCommand(command, deltaTime);
}

void SceneNode::Update(sf::Time deltaTime, CommandQueue& commandQueue)
{
	UpdateCurrent(deltaTime, commandQueue);
	UpdateChildren(deltaTime, commandQueue);
}

sf::Transform SceneNode::GetWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

const sf::Vector2f SceneNode::GetWorldPosition() const
{
	return GetWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::GetCategory() const
{
	return defaultCategory;
}

sf::FloatRect SceneNode::GetBoundingRectangle() const
{
	return  sf::FloatRect();
}

bool SceneNode::IsMarkedForRemoval() const
{
	return IsDestroyed();
}

bool SceneNode::IsDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}

void SceneNode::RemoveWrecks()
{
	// Find and remove all children which are marked for removal:
	auto wreckFieldBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::IsMarkedForRemoval));
	children.erase(wreckFieldBegin, children.end());

	// Call function recursively for all remaining children:
	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::RemoveWrecks));
}

void SceneNode::CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	CheckNodeCollision(sceneGraph, collisionPairs);

	for (NodePointer& child : sceneGraph.children)
		CheckSceneCollision(*child, collisionPairs);
}

void SceneNode::CheckNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && AreNodesCollided(*this, node) && !IsDestroyed() && !node.IsDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for (NodePointer& child : children)
		child->CheckNodeCollision(node, collisionPairs);
}

void SceneNode::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{ }

void SceneNode::UpdateChildren(sf::Time deltaTime, CommandQueue& commandQueue)
{
	for (const NodePointer& child : children)
		child->Update(deltaTime, commandQueue);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	DrawCurrent(target, states);
	DrawChildren(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{ }

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const NodePointer& child : children)
		child->draw(target, states);
}

bool AreNodesCollided(const SceneNode& left, const SceneNode& right)
{
	return left.GetBoundingRectangle().intersects(right.GetBoundingRectangle());
}

float GetDistance(const SceneNode& left, const SceneNode& right)
{
	return GetLength(left.GetWorldPosition() - right.GetWorldPosition());
}