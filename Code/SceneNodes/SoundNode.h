#pragma once

#include "SceneNode.h"
#include "../ResourceManagement/ResourceIdentifiers.h"

class SoundPlayer;

// SoundNode class is a node that contains only link to SoundPlayer. After creating
// this node, you can call "PlaySound" method to play specific sound in specific
// position on the game scene.
class SoundNode : public SceneNode
{
public:
	explicit SoundNode(SoundPlayer& soundPlayer);
	
	void PlaySound(SoundEffect::ID sound, const sf::Vector2f& position);
	virtual unsigned int GetCategory() const override;

private:
	SoundPlayer& soundPlayer;
};