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

	virtual void Init(core::Siika2D *siika);

	virtual void DeInit(core::Siika2D *siika);

private:
	bool hasBeenInit;
	misc::GameObject ushiko;
	glm::vec2 position;
	LevelGenerator *lg;
	LevelTimer *lt;
};

#endif // LEVEL