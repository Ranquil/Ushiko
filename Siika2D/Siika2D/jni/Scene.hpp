#ifndef SCENE
#define SCENE

#include "../engine/core/Siika2D.h"

enum ScreenState
{
	DEFAULT,
	MAIN_MENU,
	GAME_LEVEL
};

class Scene
{
public:
	virtual int update(core::Siika2D *siika)
	{
		return DEFAULT;
	}
};

#endif // SCENE