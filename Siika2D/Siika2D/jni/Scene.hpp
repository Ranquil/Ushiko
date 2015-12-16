#ifndef SCENE
#define SCENE

#include "../engine/core/Siika2D.h"

enum ScreenState
{
	QUIT,
	MAIN_MENU,
	GAME_OVER,
	END_SCREEN,
	LEVEL_SELECT,
	PLAINS_LEVEL,
	FOREST_LEVEL,
	CASTLE_LEVEL,
	BOSS_LEVEL
};

class Scene
{
public:
	virtual void init(core::Siika2D *siika) {}
	virtual void deInit() {}

	virtual int update(core::Siika2D *siika) { return QUIT; }

	virtual void pause() {}
	virtual void resume() {}

	glm::vec2 touchPosition;
	graphics::Sprite *bg;
};

#endif // SCENE