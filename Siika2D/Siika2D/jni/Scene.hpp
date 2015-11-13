#ifndef SCENE
#define SCENE

#include "../engine/core/Siika2D.h"

enum CollisionType
{
	USHIKO,
	GROUND,
	ENEMY,
	PROJECTILE
};

enum ScreenState
{
	QUIT,
	MAIN_MENU,
	LEVEL_SELECT,
	PLAINS_LEVEL,
	FOREST_LEVEL,
	CASTLE_LEVEL
};

class Scene
{
public:
	virtual int update(core::Siika2D *siika) { return QUIT; }

	virtual void init(core::Siika2D *siika) {}
	virtual void deInit() {}

	virtual void pause() {}
	virtual void resume() {}

	glm::vec2 touchPosition;
	graphics::Sprite *bg;
};

#endif // SCENE