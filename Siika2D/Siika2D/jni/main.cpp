#include "../engine/core/Siika2D.h"

#include "Ushiko.hpp"
#include "MainMenu.hpp"
#include "LevelSelect.hpp"
#include "Castle.hpp"

core::Siika2D *siika = core::Siika2D::UI();

Scene* scenes[4];
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
	currentScene = MAIN_MENU;

	scenes[QUIT] = new Scene;
	scenes[MAIN_MENU] = new MainMenu;
	scenes[LEVEL_SELECT] = new LevelSelect;
	scenes[CASTLE_LEVEL] = new Castle;

	scenes[currentScene]->init(siika);
}

void siika_main()
{
	int prevScene = currentScene;
	currentScene = scenes[currentScene]->update(siika);

	if (currentScene == QUIT)
	{
		// quit program
	}

	else if (currentScene != prevScene)
	{
		if (currentScene > LEVEL_SELECT)
			ushiko.init(siika);

		scenes[prevScene]->deInit();
		scenes[currentScene]->init(siika);
	}
}
