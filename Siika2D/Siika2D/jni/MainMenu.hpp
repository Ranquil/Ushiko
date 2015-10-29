#ifndef MAINMENU_H
#define MAINMENU_H

#include "../engine/core/Siika2D.h"

class MainMenu
{
public: 
	MainMenu(core::Siika2D *siika);
	~MainMenu();

	void update(core::Siika2D *siika);

private:
	misc::GameObject startGameButton;
};

#endif