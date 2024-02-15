#include "Projectile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "DataTables.h"
#include "../Commands/CommandQueue.h"
#include "../Utilities/Utilities.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "../SceneNodes/Category.h"
#include "../SceneNodes/EmitterNode.h"

namespace
{
    const std::vector<ProjectileData> ProjectileDataTable = InitializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textureHolder)
    : Entity(1)
    , type(type)
    , sprite(textureHolder.Get(ProjectileDataTable[int(type)].textureID), ProjectileDataTable[int(type)].textureRectangle)
{
    CenterOrigin(sprite);

    // Add particle system for missiles:
    if (isGuided())
    {
        auto smokePtr = std::make_unique<EmitterNode>(Particle::Type::Smoke);
        smokePtr->setPosition(0, GetBoundingRectangle().height / 2);
        AttachChild(std::move(smokePtr));

        auto propellantPtr = std::make_unique<EmitterNode>(Particle::Type::Propellant);
        propellantPtr->setPosition(0, GetBoundingRectangle().height / 2);
        AttachChild(std::move(propellantPtr));
    }
}

void Projectile::GuideTowards(sf::Vector2f position)
{
    assert(isGuided());
    targetDirection = GetUnitVector(position - GetWorldPosition());
}

bool Projectile::isGuided() const
{
    return type == Type::Missile;
}

unsigned int Projectile::GetCategory() const
{
    return type == Type::EnemyBullet ? Category::EnemyProjectile : Category::AlliedProjectile;
}

sf::FloatRect Projectile::GetBoundingRectangle() const
{
    return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

float Projectile::GetMoveSpeed() const
{
    return ProjectileDataTable[int(type)].moveSpeed;
}

int Projectile::GetDamage() const
{
    return ProjectileDataTable[int(type)].damage;
}

void Projectile::UpdateCurrent(sf::Time deltaTime, CommandQueue& commandQueue)
{
    if (isGuided())
    {
        const float APPROACH_SPEED = 200;
        
        sf::Vector2f newVelocity = GetUnitVector(targetDirection * APPROACH_SPEED * deltaTime.asSeconds() + GetVelocity());
        newVelocity *= GetMoveSpeed();
        float angle = std::atan2(newVelocity.y, newVelocity.x);

        setRotation(ConvertRadiansToDegrees(angle) + 90);
        SetVelocity(newVelocity);
    }

    Entity::UpdateCurrent(deltaTime, commandQueue);
}

void Projectile::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}