#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.hpp"

class MainMenu : public Scene
{
public: 
	MainMenu();
	~MainMenu();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box);

private:
	misc::GameObject *startGameButton;
};

#endif // MAINMENU_H