#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Level.hpp"
#include "MainMenu.hpp"

core::Siika2D *siika = core::Siika2D::UI();

void siika_onPause() {}
void siika_onResume() {}

Scene* scenes[3];
int screenState;

void siika_init()
{
	screenState = GAME_LEVEL;
	scenes[GAME_LEVEL] = new Level;
	scenes[MAIN_MENU] = new MainMenu;

	scenes[screenState]->init(siika);
}

void siika_main()
{
	int prevScene = screenState;
	screenState = scenes[screenState]->update(siika);

	if (screenState != prevScene) {
		scenes[prevScene]->deInit(siika);
		scenes[screenState]->init(siika);
	}
}
