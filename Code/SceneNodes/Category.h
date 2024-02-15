#pragma once

// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type : unsigned int
	{
		None             = 0,
		SceneAirLayer    = 1,
		PlayerAircraft   = 1 << 1,
		AlliedAircraft   = 1 << 2,
		EnemyAircraft    = 1 << 3,
		Pickup           = 1 << 4,
		AlliedProjectile = 1 << 5,
		EnemyProjectile  = 1 << 6,
		ParticleSystem   = 1 << 7,
		SoundEffect      = 1 << 8,

		Aircraft   = PlayerAircraft   | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile
	};
}