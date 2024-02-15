#pragma once

#include <SFML/Graphics/Text.hpp>

#include "SceneNode.h"
#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"

// TextNode is a node that has only text in it. You must link FontHolder
// object to it, when create this node.
class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fontHolder, const std::string& text);
	
	void SetString(const std::string& text);

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Text text;
};