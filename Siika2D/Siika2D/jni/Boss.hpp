#ifndef BOSS_H
#define BOSS_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

enum ProjectileType
{
	RETURNABLE,
	DAMAGING,
	LAST
};

struct Projectile
{
	Projectile(misc::GameObject *go, ProjectileType pt) :
		gameObject(go), projectileType(pt) {}
	~Projectile() { delete gameObject; }

	misc::GameObject *gameObject;
	ProjectileType projectileType;
};

class Boss
{
	Boss();
	~Boss();

	void update(core::Siika2D *siika);

	void init(core::Siika2D *siika);
	void deInit();

	void spawnProjectile(core::Siika2D *siika);

private:
	misc::GameObject *boss;
	std::vector<Projectile*> projectiles;
	misc::Timer projectileTimer;
	int bossHealth; 
};

#endif // BOSS_H