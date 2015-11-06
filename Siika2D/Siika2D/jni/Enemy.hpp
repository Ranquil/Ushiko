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

	void init(core::Siika2D *siika, int firstFrame = 0, int lastFrame = 0);
	void deInit();

	misc::GameObject *go;

	int xPos, yPos;
	bool hasHit;

private:
	int firstFrame;
	int lastFrame;
	std::string enemyTextureName;
	misc::Timer animationTimer;
};

#endif // ENEMY_H