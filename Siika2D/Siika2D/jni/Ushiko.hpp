#ifndef USHIKO_H
#define USHIKO_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

class Ushiko
{
public:
	Ushiko();
	~Ushiko();

	void init(core::Siika2D *siika);
	void update(core::Siika2D *siika);

	misc::GameObject *go;

	bool dashing;
	int health;
	const int healthMax = 3;
	int groundLevel;

private:
	misc::Timer jumpTimer;
	bool doubleJump;
	bool canJump;

	misc::Timer dashTimer;
	glm::vec2 originalPos;
	int xOffset;
};

extern Ushiko ushiko;

#endif // USHIKO_H