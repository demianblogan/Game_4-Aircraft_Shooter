#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.h"

// SpriteNode is a node that has only sprite in it. You must link sf::Texture
// object to it, when create this node.
class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle);

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};