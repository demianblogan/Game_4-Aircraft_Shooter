#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation(const sf::Texture& texture)
	: sprite(texture)
{ }

void Animation::SetTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

const sf::Texture* Animation::GetTexture() const
{
	return sprite.getTexture();
}

void Animation::SetFrameSize(const sf::Vector2i& frameSize)
{
	this->frameSize = frameSize;
}

const sf::Vector2i& Animation::GetFrameSize() const
{
	return frameSize;
}

void Animation::SetNumberOfFrames(int numberOfFrames)
{
	this->numberOfFrames = numberOfFrames;
}

int Animation::GetNumberOfFrames() const
{
	return numberOfFrames;
}

void Animation::SetDuration(sf::Time duration)
{
	this->duration = duration;
}

sf::Time Animation::GetDuration() const
{
	return duration;
}

void Animation::SetRepeating(bool flag)
{
	isRepeated = flag;
}

bool Animation::IsRepeated() const
{
	return isRepeated;
}

void Animation::Restart()
{
	currentFrameIndex = 0;
}

bool Animation::IsFinished() const
{
	return currentFrameIndex >= numberOfFrames;
}

const sf::FloatRect Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(GetFrameSize()));
}

const sf::FloatRect Animation::GetGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::Update(sf::Time deltaTime)
{
	sf::Time timePerFrame = duration / static_cast<float>(numberOfFrames);
	elapsedTime += deltaTime;

	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRectangle = sprite.getTextureRect();

	if (currentFrameIndex == 0)
		textureRectangle = sf::IntRect(0, 0, frameSize.x, frameSize.y);

	// While we have a frame to process:
	while (elapsedTime >= timePerFrame && (currentFrameIndex <= numberOfFrames || isRepeated))
	{
		// Move the texture rectangle left:
		textureRectangle.left += textureRectangle.width;

		// If we reach the end of the texture:
		if (textureRectangle.left + textureRectangle.width > textureBounds.x)
		{
			// Move it down one line:
			textureRectangle.left = 0;
			textureRectangle.top += textureRectangle.height;
		}

		// Progress to next frame:
		elapsedTime -= timePerFrame;
		if (isRepeated)
		{
			currentFrameIndex = (currentFrameIndex + 1) % numberOfFrames;

			if (currentFrameIndex == 0)
				textureRectangle = sf::IntRect(0, 0, frameSize.x, frameSize.y);
		}
		else
		{
			currentFrameIndex++;
		}
	}

	sprite.setTextureRect(textureRectangle);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}