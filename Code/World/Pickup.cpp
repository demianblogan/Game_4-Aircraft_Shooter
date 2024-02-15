#include "Pickup.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "DataTables.h"
#include "../Utilities/Utilities.h"
#include "../SceneNodes/Category.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
    const std::vector<PickupData> PickupDataTable = InitializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textureHolder)
    : Entity(1)
    , type(type)
    , sprite(textureHolder.Get(PickupDataTable[int(type)].textureID), PickupDataTable[int(type)].textureRectangle)
{
    CenterOrigin(sprite);
}

unsigned int Pickup::GetCategory() const
{
    return Category::Pickup;
}

sf::FloatRect Pickup::GetBoundingRectangle() const
{
    return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Pickup::Apply(Aircraft& player) const
{
    PickupDataTable[int(type)].action(player);
}

void Pickup::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}