#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Level.hpp"

#include "MainMenu.hpp"

core::Siika2D *siika = core::Siika2D::UI();

void siika_onPause() {}
void siika_onResume() {}

Scene* scenes[3];
int screenState;
//Scene *test;

void siika_init()
{
	screenState = GAME_LEVEL;
	scenes[GAME_LEVEL] = new Level();
	scenes[MAIN_MENU] = new MainMenu();

	//test = new Level(siika);
}

void siika_main()
{
	screenState = scenes[screenState]->update(siika);
	//test->update(siika);
}
