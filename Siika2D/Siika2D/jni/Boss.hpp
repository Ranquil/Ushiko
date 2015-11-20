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
	int xPos, yPos;
};

class Boss
{
public:
	Boss();
	~Boss();

	void update(core::Siika2D *siika);

	void init(core::Siika2D *siika);
	void deInit();

	void spawnProjectile(core::Siika2D *siika);

	void isIntersecting(glm::vec2 projectilePosition);

private:
	misc::GameObject *boss;
	std::vector<Projectile*> projectiles;
	misc::Timer projectileTimer;
	int bossHealth; 
	glm::vec2 screenSize;
};

#endif // BOSS_H