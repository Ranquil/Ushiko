#ifndef USHIKO
#define USHIKO

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

private:
	misc::Timer tempTimer;
	bool canJump;
};

extern Ushiko ushiko;

#endif // USHIKO