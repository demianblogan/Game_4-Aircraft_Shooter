#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include "../SceneNodes/Category.h"

class SceneNode;

// The Command structure stores the category of the object to
// which the action needs to be applied, as well as the action
// itself. All objects on the stage are child classes of SceneNode,
// and each of them has its own category.
struct Command
{
	using Action = std::function<void(SceneNode&, sf::Time)>;

	Action action;
	unsigned int category = Category::None;
};

template <typename GameObject, typename Function>
Command::Action GetDerivedAction(Function function)
{
	auto derivedActionFunction = [=](SceneNode& node, sf::Time deltaTime)
		{
			// Check is cast if safe:
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// Downcast node and invoke function on it:
			function(static_cast<GameObject&>(node), deltaTime);
		};

	return derivedActionFunction;
}