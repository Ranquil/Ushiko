#ifndef BOSS_H
#define BOSS_H
#include "../engine/core/Siika2D.h"
#include "../engine/misc/Timer.h"

class Boss
{
	enum ProjectileType
	{
		RETURNABLE,
		DAMAGING
	};
	struct Projectile
	{
		Projectile(misc::GameObject *go, ProjectileType pt) : gameObject(go), projectileType(pt) {}
		~Projectile() { delete gameObject; }
		misc::GameObject *gameObject;
		ProjectileType projectileType;
	};
	Boss();
	~Boss();

	void init(core::Siika2D *siika);
	void deInit();
	void update(core::Siika2D *siika);

	void spawnProjectile(core::Siika2D *siika);

private:
	misc::GameObject *boss;
	std::vector<Projectile*> projectiles;

	misc::Timer projectileTimer;
};

#endif