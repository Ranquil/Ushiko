#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.hpp"
#include "Enemy.hpp"

class MainMenu : public Scene
{
public: 
	MainMenu();
	~MainMenu();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();
	Enemy *test;

private:
	misc::GameObject startGameButton;
};

#endif // MAINMENU_H