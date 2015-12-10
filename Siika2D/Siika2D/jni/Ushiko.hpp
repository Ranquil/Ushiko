#ifndef USHIKO_H
#define USHIKO_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

#include <map>

class Ushiko
{
	enum animState
	{
		IDLE,
		RUN,
		DASH,
		JUMP_START,
		JUMP_MIDDLE,
		JUMP_END,
		DOUBLE_JUMP
	};
	typedef struct {
		unsigned int sheet;
		unsigned int startPos;
		unsigned int frames;
		bool loop;
	} animation;

	animState currentAnimation;
	unsigned int currentFrame;

	std::map<animState, animation> animations;
	misc::Timer animTimer;

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
	int enemiesKilled;

	misc::GameObject *go;

private:
	unsigned int prevChange;
	void changeSheet(core::Siika2D *siika, unsigned int sheetNum);

	bool canJump;
	bool doubleJump;
	misc::Timer jumpTimer;
	misc::Timer airTimer;

	int xOffset;
	glm::vec2 originalPos;
	misc::Timer dashTimer;
};

extern Ushiko ushiko;

#endif // USHIKO_H