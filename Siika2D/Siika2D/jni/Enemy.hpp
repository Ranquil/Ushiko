#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

class Enemy
{
public:
	Enemy(std::string enemyTextureName, bool fourByfour = false);
	~Enemy();

	void update(core::Siika2D *siika);

	void init(core::Siika2D *siika, int firstFrame = 0, int lastFrame = 0, int animeSpeed = 200);
	void deInit();

	int xPos, yPos, yLevel;
	bool hasHit;
	bool flies;
	bool rising;

	misc::GameObject *go;

private:
	bool fbf;
	int firstFrame;
	int lastFrame;
	int animeSpeed;

	std::string enemyTextureName;
	misc::Timer animationTimer;
};

#endif // ENEMY_H