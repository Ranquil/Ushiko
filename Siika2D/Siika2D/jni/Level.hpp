#ifndef LEVEL
#define LEVEL

#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"

#include <Box2D/Box2D.h>

#include "LevelGenerator.hpp"
#include "LevelTimer.hpp"

class Level
{
public:

	Level(core::Siika2D *siika);
	~Level();

	void update(core::Siika2D *siika);
private:
	misc::GameObject ushiko;
	glm::vec2 position;
	LevelGenerator *lg;
	LevelTimer *lt;

};

#endif