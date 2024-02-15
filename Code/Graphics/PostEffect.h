#pragma once

#include <SFML/System/NonCopyable.hpp>

namespace sf
{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

// Game can support post effects. Post effect is an effect that is applied to
// a complete frame just before it's showed on the window. Class PostEffect
// is a base class for all post effect classes.
class PostEffect : private sf::NonCopyable
{
public:
	virtual ~PostEffect();

	virtual void Apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;
	static bool IsSupported();

protected:
	static void ApplyShader(const sf::Shader& shader, sf::RenderTarget& output);
};