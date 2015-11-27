#ifndef USHIKO_H
#define USHIKO_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

enum animState
{
	IDLE,
	RUN,
	DASH,
	JUMP_START,
	JUMP_MIDDLE,
	JUMP_END,
	MAGIC
};

class Ushiko
{
public:
	Ushiko();
	~Ushiko();

	void init(core::Siika2D *siika);
	void update(core::Siika2D *siika);

	bool dashing;
	const int healthMax = 3;
	const int maxCoins = 10;

	int groundLevel;
	int health;
	int coinCount;
	int pointsAmount;

	misc::GameObject *go;

private:
	animState anim;
	void animate(int prev);
	misc::Timer animTimer;

	bool canJump;
	bool doubleJump;
	misc::Timer jumpTimer;

	int xOffset;
	glm::vec2 originalPos;
	misc::Timer dashTimer;
};

extern Ushiko ushiko;

#endif // USHIKO_H