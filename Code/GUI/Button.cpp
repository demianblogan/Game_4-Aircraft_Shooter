#include "Button.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../Audio/SoundPlayer.h"
#include "../Utilities/Utilities.h"

GUI::Button::Button(State::Context context)
	: sprite(context.textureHolder->Get(Texture::ID::Buttons))
	, text("", context.fontHolder->Get(Font::ID::Main), 16)
	, soundPlayer(*context.soundPlayer)
{
	ChangeTexture(Type::Normal);

	sf::FloatRect bounds = sprite.getLocalBounds();
	text.setPosition(bounds.width / 2, bounds.height / 2);
}

void GUI::Button::SetCallback(Callback callback)
{
	this->callback = std::move(callback);
}

void GUI::Button::SetText(const std::string& text)
{
	this->text.setString(text);
	CenterOrigin(this->text);
}

void GUI::Button::SetToggle(bool flag)
{
	isToggle = flag;
}

bool GUI::Button::IsSelectable() const
{
	return true;
}

void GUI::Button::Select()
{
	Component::Select();
	ChangeTexture(Type::Selected);
}

void GUI::Button::Deselect()
{
	Component::Deselect();
	ChangeTexture(Type::Normal);
}

void GUI::Button::Activate()
{
	Component::Activate();

	// If the button is toggle then we should show that the button is pressed and thus "toggled":
	if (isToggle)
		ChangeTexture(Type::Pressed);

	if (callback != nullptr)
		callback();

	// If the button isn't a toggle then deactivate the button since we just momentarily activated it.
	if (!isToggle)
		Deactivate();

	soundPlayer.Play(SoundEffect::ID::Button);
}

void GUI::Button::Deactivate()
{
	Component::Deactivate();

	if (isToggle)
		ChangeTexture(IsSelected() ? Type::Selected : Type::Normal);
}

void GUI::Button::HandleEvent(const sf::Event& event)
{ }

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
	target.draw(text, states);
}

void GUI::Button::ChangeTexture(Type buttonType)
{
	sf::IntRect textureRectangle(0, 50 * int(buttonType), 200, 50);
	sprite.setTextureRect(textureRectangle);
}