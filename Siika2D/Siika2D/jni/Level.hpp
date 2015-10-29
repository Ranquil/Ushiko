#ifndef LEVEL
#define LEVEL

#include "Scene.hpp"
#include "../engine/misc/GameObject.h"

#include "LevelGenerator.hpp"
#include "LevelTimer.hpp"


class Level : public Scene
{
public:
	Level(core::Siika2D *siika);
	~Level();

	virtual int update(core::Siika2D *siika);

private:
	misc::GameObject ushiko;
	glm::vec2 position;
	LevelGenerator *lg;
	LevelTimer *lt;
};

#endif // LEVEL