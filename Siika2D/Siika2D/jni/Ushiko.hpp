#ifndef USHIKO_H
#define USHIKO_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

enum animState {
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
	int groundLevel;
	int health;

	const int healthMax = 3;

	misc::GameObject *go;

	int gemCount;
	const int maxGems = 20;
	int pointsAmount;

private:
	void animate(int prev);
	animState anim;
	misc::Timer animTimer;

	misc::Timer jumpTimer;
	bool doubleJump;
	bool canJump;

	misc::Timer dashTimer;
	glm::vec2 originalPos;
	int xOffset;
};

extern Ushiko ushiko;

#endif // USHIKO_H