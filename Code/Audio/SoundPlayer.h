#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"

// The SoundPlayer class is a class that holds all the sounds that are
// played in the game and provides methods for playing them and setting the location of the listener.
class SoundPlayer : private sf::NonCopyable
{
public:
	SoundPlayer();

	void Play(SoundEffect::ID effect);
	void Play(SoundEffect::ID effect, const sf::Vector2f& position);

	void RemoveStoppedSounds();
	void SetListenerPosition(const sf::Vector2f& position);
	const sf::Vector2f GetListenerPosition() const;

private:
	SoundBufferHolder soundBuffersHolder;
	std::list<sf::Sound> soundsList;
};