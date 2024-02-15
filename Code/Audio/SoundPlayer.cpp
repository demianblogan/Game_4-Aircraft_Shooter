#include "SoundPlayer.h"

#include <SFML/Audio/Listener.hpp>

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float LISTENER_Z = 300;
	const float ATTENUATION = 8;
	const float MIN_DISTANCE_2D = 200;
	const float MIN_DISTANCE_3D = std::sqrt(MIN_DISTANCE_2D * MIN_DISTANCE_2D + LISTENER_Z * LISTENER_Z);
}

SoundPlayer::SoundPlayer()
{
	soundBuffersHolder.Load(SoundEffect::ID::AlliedGunFire, "Resources/Audio/Sounds/AlliedGunfire.wav");
	soundBuffersHolder.Load(SoundEffect::ID::EnemyGunFire, "Resources/Audio/Sounds/EnemyGunfire.wav");
	soundBuffersHolder.Load(SoundEffect::ID::Explosion1, "Resources/Audio/Sounds/Explosion1.wav");
	soundBuffersHolder.Load(SoundEffect::ID::Explosion2, "Resources/Audio/Sounds/Explosion2.wav");
	soundBuffersHolder.Load(SoundEffect::ID::LaunchMissile, "Resources/Audio/Sounds/LaunchMissile.wav");
	soundBuffersHolder.Load(SoundEffect::ID::CollectPickup, "Resources/Audio/Sounds/CollectPickup.wav");
	soundBuffersHolder.Load(SoundEffect::ID::Button, "Resources/Audio/Sounds/Button.wav");

	// Listener points towards the screen (default in SFML):
	sf::Listener::setDirection(0, 0, -1);
}

void SoundPlayer::Play(SoundEffect::ID effect)
{
	Play(effect, GetListenerPosition());
}

void SoundPlayer::Play(SoundEffect::ID effect, const sf::Vector2f& position)
{
	soundsList.push_back(sf::Sound());
	sf::Sound& sound = soundsList.back();

	sound.setBuffer(soundBuffersHolder.Get(effect));
	sound.setPosition(position.x, -position.y, 0);
	sound.setAttenuation(ATTENUATION);
	sound.setMinDistance(MIN_DISTANCE_3D);

	sound.play();
}

void SoundPlayer::RemoveStoppedSounds()
{
	auto remover = [](const sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; };
	soundsList.remove_if(remover);
}

void SoundPlayer::SetListenerPosition(const sf::Vector2f& position)
{
	sf::Listener::setPosition(position.x, -position.y, LISTENER_Z);
}

const sf::Vector2f SoundPlayer::GetListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}