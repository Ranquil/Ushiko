#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.hpp"

#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

class MainMenu : public Scene
{
public: 
	MainMenu();
	~MainMenu();

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual int update(core::Siika2D *siika);

private:
	bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box);

	misc::GameObject *startGameButton;
	graphics::Sprite *logo;
	misc::Timer initTimer;

	bool playSound;
	bool hasBeenInit;
};

#endif // MAINMENU_H