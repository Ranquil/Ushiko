#include "../engine/core/Siika2D.h"

#include "Ushiko.hpp"
#include "MainMenu.hpp"
#include "LevelSelect.hpp"
#include "Level.hpp"

core::Siika2D *siika = core::Siika2D::UI();

Scene* scenes[7];
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
	misc::File *file = siika->getFile("progress.txt");
	std::string read = file->readFile();

	if (read.find("1") == std::string::npos) // Comment this line out to always reset progress on launch
		file->writeFile("0");

	currentScene = MAIN_MENU;

	scenes[QUIT] = new Scene;
	scenes[MAIN_MENU] = new MainMenu;
	scenes[LEVEL_SELECT] = new LevelSelect;
	scenes[PLAINS_LEVEL] = new Level("plains");
	scenes[FOREST_LEVEL] = new Level("forest");
	scenes[CASTLE_LEVEL] = new Level("castle");
	scenes[BOSS_LEVEL] = new Level("boss");

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
