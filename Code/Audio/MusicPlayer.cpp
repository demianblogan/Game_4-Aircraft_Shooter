#include "MusicPlayer.h"

#include <stdexcept>

#include "../ResourceManagement/ResourceIdentifiers.h"

MusicPlayer::MusicPlayer()
{
	filenamesMap[Music::ID::MenuTheme] = "Resources/Audio/Music/MenuTheme.ogg";
	filenamesMap[Music::ID::MissionTheme] = "Resources/Audio/Music/MissionTheme.ogg";
}

void MusicPlayer::Play(Music::ID theme)
{
	const std::string& filename = filenamesMap[theme];

	if (!music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void MusicPlayer::Stop()
{
	music.stop();
}

void MusicPlayer::SetPaused(bool isPaused)
{
	isPaused ? music.pause() : music.play();
}

void MusicPlayer::SetVolume(float volume)
{
	this->volume = volume;
}