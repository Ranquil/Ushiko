#ifndef HEARTSPLOSION_H
#define HEARTSPOLISON_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
//#include "../engine/misc/Timer.h"

class Heartsplosion
{
public:
	Heartsplosion();
	~Heartsplosion();

	void init(core::Siika2D *siika, int x, int y);
	void update();

	int xPos, yPos;
//	float lifeTime;
//	misc::Timer lifeTimer;
	misc::GameObject *go;

private:
	glm::vec2 force;
};

#endif // HEARTSPLOSION_H