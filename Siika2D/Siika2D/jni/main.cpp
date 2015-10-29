#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"

#include <Box2D/Box2D.h>

#include "Level.hpp"

enum ScreenState{
	MAIN_MENU,
	GAME_LEVEL
};
core::Siika2D *siika = core::Siika2D::UI();
Level *level;
ScreenState screenState;

void siika_onPause() {}
void siika_onResume() {}


void siika_init()
{
	screenState = MAIN_MENU;
}

void siika_main()
{

	switch (screenState)
	{
		case MAIN_MENU:

		break;

		case GAME_LEVEL:
		level = new Level(siika);
		level->update(siika);
		break;
	}

	
}
