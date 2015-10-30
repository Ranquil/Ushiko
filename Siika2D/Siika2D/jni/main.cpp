#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Castle.hpp"
#include "MainMenu.hpp"
#include "LevelSelect.hpp"
#include "Ushiko.hpp"

misc::Timer switchTimer;

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

	currentScene = CASTLE_LEVEL;

	scenes[MAIN_MENU] = new MainMenu;
	scenes[LEVEL_SELECT] = new LevelSelect;
	scenes[CASTLE_LEVEL] = new Castle;

	scenes[currentScene]->init(siika);

	switchTimer.start();
}

void siika_main()
{
	int prevScene = currentScene;
	currentScene = scenes[currentScene]->update(siika);

	if (switchTimer.getElapsedTime(MILLISECONDS) > 10000)
	{
		currentScene += 1;
		int sceneNum = 0;

		for (Scene *s : scenes)
			sceneNum += 1;

		if (currentScene >= sceneNum)
			currentScene = 0;

		switchTimer.reset();
	}

	if (currentScene != prevScene)
	{
		scenes[prevScene]->deInit(siika);
		siika->_graphicsContext->clear();
		scenes[currentScene]->init(siika);
	}
}
