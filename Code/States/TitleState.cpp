#include "TitleState.h"

#include <SFML/Window/Event.hpp>

#include "../Utilities/Utilities.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	backgroundSprite.setTexture(context.textureHolder->Get(Texture::ID::TitleScreen));

	titleText.setFont(context.fontHolder->Get(Font::ID::Main));
	titleText.setString("Press any key to start");
	CenterOrigin(titleText);
	titleText.setPosition(context.window->getView().getSize() / 2.0f);
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	// If any key has been pressed, then trigger the next screen:
	if (event.type == sf::Event::KeyReleased)
	{
		RequestStackPop();
		RequestStackPush(State::ID::Menu);
	}

	return true;
}

bool TitleState::Update(sf::Time deltaTime)
{
	textBlinkingEffectTime += deltaTime;
	if (textBlinkingEffectTime >= sf::seconds(0.5f))
	{
		needToShowTitleText = !needToShowTitleText;
		textBlinkingEffectTime = sf::Time::Zero;
	}

	return true;
}

void TitleState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.draw(backgroundSprite);

	if (needToShowTitleText)
		window.draw(titleText);
}