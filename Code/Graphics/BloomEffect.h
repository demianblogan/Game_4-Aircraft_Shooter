#pragma once

#include <array>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "PostEffect.h"
#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"

// BloomEffect class presents a bloom effect that is applied to some game's entities
// (like bullets, etc.). It contains algorithms like blurring maltipass, downsampling, etc.
// to implement bloom effect.
class BloomEffect : public PostEffect
{
public:
	BloomEffect();

	virtual void Apply(const sf::RenderTexture& input, sf::RenderTarget& output) override;

private:
	using RenderTextureArray = std::array<sf::RenderTexture, 2>;

	void PrepareTextures(const sf::Vector2u size);

	void FilterBright(const sf::RenderTexture& input, sf::RenderTexture& output);
	void BlurMultipass(RenderTextureArray& renderTexturesArray);
	void Blur(const sf::RenderTexture& input, sf::RenderTexture& output, const sf::Vector2f& offsetFactor);
	void Downsample(const sf::RenderTexture& input, sf::RenderTexture& output);
	void Add(const sf::RenderTexture& source, sf::RenderTexture& bloom, sf::RenderTarget& target);

	ShaderHolder shaderHolder;
	sf::RenderTexture brightnessTexture;
	RenderTextureArray firstPassTexturesArray;
	RenderTextureArray secondPassTexturesArray;
};