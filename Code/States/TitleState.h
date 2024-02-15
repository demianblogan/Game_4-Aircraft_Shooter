#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"

// Title state is the first state you'll see when launch the game. It's just
// a background picture, with music and blinking text.
class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;

private:
	sf::Sprite backgroundSprite;

	sf::Text titleText;
	bool needToShowTitleText = true;
	sf::Time textBlinkingEffectTime = sf::Time::Zero;
};