#ifndef PUFF_HEADER
#define PUFF_HEADER

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

class Puff
{
public:
	Puff();
	~Puff();

	void init(core::Siika2D *siika, int x, int y);
	void update(core::Siika2D *siika);

	misc::GameObject *go;
	int xPos, yPos;

private:
	misc::Timer animTimer;
	int animSteps;
};

#endif // PUFF_HEADER