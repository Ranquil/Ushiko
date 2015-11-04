#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Castle.hpp"
#include "MainMenu.hpp"
#include "LevelSelect.hpp"
#include "Ushiko.hpp"

core::Siika2D *siika = core::Siika2D::UI();
//misc::Timer switchTimer;

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
	ushiko.init(siika);

	currentScene = MAIN_MENU;

	scenes[QUIT] = new Scene;
	scenes[MAIN_MENU] = new MainMenu;
	scenes[LEVEL_SELECT] = new LevelSelect;
	scenes[CASTLE_LEVEL] = new Castle;

	scenes[currentScene]->init(siika);

	//switchTimer.start();
}

void siika_main()
{
	int prevScene = currentScene;
	currentScene = scenes[currentScene]->update(siika);

	/*if (switchTimer.getElapsedTime(MILLISECONDS) > 10000)
	{
		currentScene += 1;
		int sceneNum = 0;

		for (Scene *s : scenes)
			sceneNum += 1;

		if (currentScene >= sceneNum)
			currentScene = 0;

		switchTimer.reset();
	}*/

	if (currentScene != prevScene)
	{
		scenes[prevScene]->deInit();
		scenes[currentScene]->init(siika);
	}

	if (currentScene == QUIT)
	{
		// quit program
	}
}
