#pragma once

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

// This file contains all resource identifiers of the game. They're used
// as keys for ResourceHolder class.

namespace Texture
{
	enum class ID
	{
		Entities,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine
	};
}

namespace Font
{
	enum class ID
	{
		Main
	};
}

namespace Shader
{
	enum class ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass
	};
}

namespace SoundEffect
{
	enum class ID
	{
		AlliedGunFire,
		EnemyGunFire,
		Explosion1,
		Explosion2,
		LaunchMissile,
		CollectPickup,
		Button
	};
}

namespace Music
{
	enum class ID
	{
		MenuTheme,
		MissionTheme
	};
}

template <typename Identifier, typename Resource>
class ResourceHolder;

using TextureHolder = ResourceHolder<Texture::ID, sf::Texture>;
using FontHolder = ResourceHolder<Font::ID, sf::Font>;
using ShaderHolder = ResourceHolder<Shader::ID, sf::Shader>;
using SoundBufferHolder = ResourceHolder<SoundEffect::ID, sf::SoundBuffer>;