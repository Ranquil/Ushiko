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

	void init(core::Siika2D *siika, int firstFrame = 0, int lastFrame = 0, int animeSpeed = 200);
	void deInit();

	void update(core::Siika2D *siika);

	bool flies;
	bool rising;
	bool hasHit;
	int xPos, yPos;
	int yLevel;

	misc::GameObject *go;

private:
	bool fbf;
	int firstFrame;
	int lastFrame;
	int animeSpeed;

	std::string enemyTextureName;
	misc::Timer animationTimer;
	misc::Timer inkBallTimer;
};

#endif // ENEMY_H