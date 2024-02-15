#include "SoundNode.h"

#include "../Audio/SoundPlayer.h"

SoundNode::SoundNode(SoundPlayer& soundPlayer)
    : soundPlayer(soundPlayer)
{ }

void SoundNode::PlaySound(SoundEffect::ID sound, const sf::Vector2f& position)
{
    soundPlayer.Play(sound, position);
}

unsigned int SoundNode::GetCategory() const
{
    return Category::SoundEffect;
}