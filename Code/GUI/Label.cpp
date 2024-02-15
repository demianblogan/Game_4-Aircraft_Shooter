#include "Label.h"
#include <SFML/Graphics/RenderTarget.hpp>

GUI::Label::Label(const std::string& text, const FontHolder& fontHolder)
	: text(text, fontHolder.Get(Font::ID::Main), 16)
{ }

bool GUI::Label::IsSelectable() const
{
	return false;
}

void GUI::Label::HandleEvent(const sf::Event& event)
{ }

void GUI::Label::SetText(const std::string& text)
{
	this->text.setString(text);
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}