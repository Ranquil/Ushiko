#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "../engine/core/Siika2D.h"

class Collectable
{
public:
	Collectable();
	~Collectable();

	void init(core::Siika2D *siika);
	void deinit();

	int xPos, yPos;
	misc::GameObject *go;
};

#endif //COLLECTABLE_H