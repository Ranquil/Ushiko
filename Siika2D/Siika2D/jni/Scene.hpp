#ifndef SCENE
#define SCENE

#include "../engine/core/Siika2D.h"

enum ScreenState
{
	MAIN_MENU,
	LEVEL_SELECT,
	CASTLE_LEVEL
};

class Scene
{
public:
	virtual int update(core::Siika2D *siika) { return 0; }

	virtual void init(core::Siika2D *siika) {}
	virtual void deInit(core::Siika2D *siika) {}

	virtual void pause() {}
	virtual void resume() {}

	bool lvl2Unlocked;
	bool lvl3Unlocked;
	glm::vec2 touchPosition;
};

#endif // SCENE