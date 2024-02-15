#pragma once

#include <cassert>
#include <unordered_map>
#include <memory>
#include <stdexcept>

// SFML has a lot of resources: sf::Sound, sf::Music, sf::SoundBuffer, sf::Picture,
// sf::Texture, sf::Sprite, sf::Text, sf::Font, sf::Shader. All of them have some similar
// methods, like "loadFromFile". So I decided to create a container for all of those
// types (pictures, sounds, shaders, texts). It's a simple std::unordered_map object,
// that has "Load" and "Get" methods. All keys are in "ResourceIdentifiers.h" file.
template <typename Identifier, typename Resource>
class ResourceHolder
{
public:
	void Load(Identifier id, const std::string& filename)
	{
		auto resource = std::make_unique<Resource>();
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);

		auto inserted = resourceMap.insert({ id, std::move(resource) });
		assert(inserted.second);
	}

	template <typename Parameter>
	void Load(Identifier id, const std::string& filename, const Parameter& secondParameter)
	{
		auto resource = std::make_unique<Resource>();
		if (!resource->loadFromFile(filename, secondParameter))
			throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);

		auto inserted = resourceMap.insert({ id, std::move(resource) });
		assert(inserted.second);
	}

	Resource& Get(Identifier id)
	{
		auto foundIterator = resourceMap.find(id);
		assert(foundIterator != resourceMap.cend());

		return *foundIterator->second;
	}

	const Resource& Get(Identifier id) const
	{
		auto foundIterator = resourceMap.find(id);
		assert(foundIterator != resourceMap.cend());

		return *foundIterator->second;
	}

private:
	std::unordered_map<Identifier, std::unique_ptr<Resource>> resourceMap;
};