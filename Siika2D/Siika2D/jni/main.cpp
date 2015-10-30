#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Castle.hpp"
#include "MainMenu.hpp"
#include "LevelSelect.hpp"
#include "Ushiko.hpp"

core::Siika2D *siika = core::Siika2D::UI();

Scene* scenes[3];
int currentScene;

void siika_onPause()
{
	scenes[currentScene]->pause();
}

void siika_onResume()
{
	scenes[currentScene]->resume();
}

void siika_init()
{
	ushiko.init(siika);

	//currentScene = CASTLE_LEVEL;
	//currentScene = MAIN_MENU;
	currentScene = LEVEL_SELECT;
	scenes[MAIN_MENU] = new MainMenu;
	scenes[LEVEL_SELECT] = new LevelSelect;
	scenes[CASTLE_LEVEL] = new Castle;

	scenes[currentScene]->init(siika);
}

void siika_main()
{
	int prevScene = currentScene;
	currentScene = scenes[currentScene]->update(siika);

	if (currentScene != prevScene)
	{
		scenes[prevScene]->deInit(siika);
		scenes[currentScene]->init(siika);
	}
}
