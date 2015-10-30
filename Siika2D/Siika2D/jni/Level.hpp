#ifndef LEVEL
#define LEVEL

#include "Scene.hpp"
#include "LevelGenerator.hpp"
#include "LevelTimer.hpp"

class Level : public Scene
{
public:
	Level();
	~Level();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit(core::Siika2D *siika);

private:
	misc::GameObject ushiko;
	glm::vec2 position;
	LevelGenerator *lg;
	LevelTimer *lt;
	colListener collisionListener;

	misc::Timer tempTimer;
	bool canJump;
};

#endif // LEVEL