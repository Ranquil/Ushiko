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
	void update(core::Siika2D *siika, colListener *collisions);

	void dash(core::Siika2D *siika);

	misc::GameObject *go;

	int groundLevel;

private:
	misc::Timer jumpTimer;
	bool doubleJump;
	bool canJump;

	misc::Timer dashTimer;
	bool dashing;
	int xOffset;
	int xOrigin;
	int yOrigin;
};

extern Ushiko ushiko;

#endif // USHIKO_H