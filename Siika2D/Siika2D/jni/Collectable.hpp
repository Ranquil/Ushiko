#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/Timer.h"

class Collectable
{
public:
	Collectable();
	~Collectable();

	void init(core::Siika2D *siika);
	void deinit();

	void update();

	int xPos, yPos;
	misc::GameObject *go;

private:
	misc::Timer animTimer;
};

#endif //COLLECTABLE_H