#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

// Animation is a class that implements the ability to animate sprites.
// When creating an object of this class, you can pass it a texture,
// which will be a sprite sheet, and thanks to its methods, you can get
// different sprites from this sprite sheet and configure the animation
// itself, for example its speed, the number of frames in the sprite sheet,
// and so on.
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation() = default;
	explicit Animation(const sf::Texture& texture);

	void SetTexture(const sf::Texture& texture);
	const sf::Texture* GetTexture() const;

	void SetFrameSize(const sf::Vector2i& frameSize);
	const sf::Vector2i& GetFrameSize() const;

	void SetNumberOfFrames(int numberOfFrames);
	int GetNumberOfFrames() const;

	void SetDuration(sf::Time duration);
	sf::Time GetDuration() const;

	void SetRepeating(bool flag);
	bool IsRepeated() const;

	void Restart();
	bool IsFinished() const;

	const sf::FloatRect getLocalBounds() const;
	const sf::FloatRect GetGlobalBounds() const;

	void Update(sf::Time deltaTime);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
	sf::Vector2i frameSize;
	int numberOfFrames = 0;
	int currentFrameIndex = 0;
	sf::Time duration = sf::Time::Zero;
	sf::Time elapsedTime = sf::Time::Zero;
	bool isRepeated = false;
};