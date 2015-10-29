#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.hpp"

class MainMenu : public Scene
{
public: 
	MainMenu(core::Siika2D *siika);
	~MainMenu();

	virtual int update(core::Siika2D *siika);

private:
	misc::GameObject startGameButton;
};

#endif // MAINMENU