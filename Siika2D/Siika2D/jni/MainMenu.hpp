#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.hpp"

class MainMenu : public Scene
{
public: 
	MainMenu();
	~MainMenu();

	virtual int update(core::Siika2D *siika);

	virtual void Init(core::Siika2D *siika);

	virtual void DeInit(core::Siika2D *siika);

private:
	bool hasBeenInit;
	misc::GameObject startGameButton;
};

#endif // MAINMENU