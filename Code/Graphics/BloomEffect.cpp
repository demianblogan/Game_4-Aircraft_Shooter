#include "BloomEffect.h"

BloomEffect::BloomEffect()
{
	shaderHolder.Load(Shader::ID::BrightnessPass, "Resources/Shaders/Fullpass.vert", "Resources/Shaders/Brightness.frag");
	shaderHolder.Load(Shader::ID::DownSamplePass, "Resources/Shaders/Fullpass.vert", "Resources/Shaders/DownSample.frag");
	shaderHolder.Load(Shader::ID::GaussianBlurPass, "Resources/Shaders/Fullpass.vert", "Resources/Shaders/GuassianBlur.frag");
	shaderHolder.Load(Shader::ID::AddPass, "Resources/Shaders/Fullpass.vert", "Resources/Shaders/Add.frag");
}

void BloomEffect::Apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{
	PrepareTextures(input.getSize());

	FilterBright(input, brightnessTexture);

	Downsample(brightnessTexture, firstPassTexturesArray[0]);
	BlurMultipass(firstPassTexturesArray);

	Downsample(firstPassTexturesArray[0], secondPassTexturesArray[0]);
	BlurMultipass(secondPassTexturesArray);

	Add(firstPassTexturesArray[0], secondPassTexturesArray[0], firstPassTexturesArray[1]);
	firstPassTexturesArray[1].display();
	Add(input, firstPassTexturesArray[1], output);
}

void BloomEffect::PrepareTextures(const sf::Vector2u size)
{
	if (brightnessTexture.getSize() != size)
	{
		brightnessTexture.create(size.x, size.y);
		brightnessTexture.setSmooth(true);

		firstPassTexturesArray[0].create(size.x / 2, size.y / 2);
		firstPassTexturesArray[0].setSmooth(true);
		firstPassTexturesArray[1].create(size.x / 2, size.y / 2);
		firstPassTexturesArray[1].setSmooth(true);

		secondPassTexturesArray[0].create(size.x / 4, size.y / 4);
		secondPassTexturesArray[0].setSmooth(true);
		secondPassTexturesArray[1].create(size.x / 4, size.y / 4);
		secondPassTexturesArray[1].setSmooth(true);
	}
}

void BloomEffect::FilterBright(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	sf::Shader& brightness = shaderHolder.Get(Shader::ID::BrightnessPass);
	brightness.setUniform("source", input.getTexture());
	ApplyShader(brightness, output);
	output.display();
}

void BloomEffect::BlurMultipass(RenderTextureArray& renderTexturesArray)
{
	sf::Vector2u textureSize = renderTexturesArray[0].getSize();

	for (int i = 0; i < 2; i++)
	{
		Blur(renderTexturesArray[0], renderTexturesArray[1], sf::Vector2f(0, 1.0f / textureSize.y));
		Blur(renderTexturesArray[1], renderTexturesArray[0], sf::Vector2f(1.0f / textureSize.x, 0));
	}
}

void BloomEffect::Blur(const sf::RenderTexture& input, sf::RenderTexture& output, const sf::Vector2f& offsetFactor)
{
	sf::Shader& gaussianBlur = shaderHolder.Get(Shader::ID::GaussianBlurPass);

	gaussianBlur.setUniform("source", input.getTexture());
	gaussianBlur.setUniform("offsetFactor", offsetFactor);
	ApplyShader(gaussianBlur, output);

	output.display();
}

void BloomEffect::Downsample(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	sf::Shader& downSampler = shaderHolder.Get(Shader::ID::DownSamplePass);

	downSampler.setUniform("source", input.getTexture());
	downSampler.setUniform("sourceSize", sf::Vector2f(input.getSize()));
	ApplyShader(downSampler, output);
	output.display();
}

void BloomEffect::Add(const sf::RenderTexture& source, sf::RenderTexture& bloom, sf::RenderTarget& target)
{
	sf::Shader& adder = shaderHolder.Get(Shader::ID::AddPass);

	adder.setUniform("source", source.getTexture());
	adder.setUniform("bloom", bloom.getTexture());
	ApplyShader(adder, target);
}