#pragma once

#include <map>

#include <SFML/Audio/Music.hpp>

namespace Music
{
	enum class ID;
}

// The MusicPlayer class is a class that holds all the music
// that is played in the game and provides methods for turning
// it on, off, pausing, and adjusting the volume.
class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();

	void Play(Music::ID theme);
	void Stop();

	void SetPaused(bool isPaused);
	void SetVolume(float volume);

private:
	sf::Music music;
	std::map<Music::ID, std::string> filenamesMap;
	float volume = 100.0f;
};