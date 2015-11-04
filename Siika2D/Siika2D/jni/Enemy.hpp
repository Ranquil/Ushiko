#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

class Enemy
{
public:
	Enemy(std::string enemyTextureName);
	~Enemy();

	void update(core::Siika2D *siika);

	void init(core::Siika2D *siika);
	void deInit();

private:
	misc::GameObject *go;
	std::string enemyTextureName;
	misc::Timer animationTimer;
};

#endif // ENEMY_H