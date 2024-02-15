#include "TextNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../Utilities/Utilities.h"

TextNode::TextNode(const FontHolder& fontHolder, const std::string& text)
{
	this->text.setFont(fontHolder.Get(Font::ID::Main));
	this->text.setCharacterSize(20);
	SetString(text);
}

void TextNode::SetString(const std::string& text)
{
	this->text.setString(text);
	CenterOrigin(this->text);
}

void TextNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}