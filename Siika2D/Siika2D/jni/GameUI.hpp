#ifndef GAMEUI_H
#define GAMEUI_H

#include "LevelTimer.hpp"

enum UIState
{
	DEFAULT,
	PAUSE,
	RESUME
};

class GameUI
{
public:
	GameUI();
	~GameUI();

	int update(core::Siika2D *siika);

	void init(core::Siika2D *siika);
	void deInit();

	void changeTexture(misc::GameObject *gameObject, core::Siika2D *siika, std::string newTextureName, glm::vec2 size);

	LevelTimer *lt;

private:
	int heartCount;

	UIState lastState;

	graphics::Text *gemTextUI;
	graphics::Sprite *shade;

	std::vector<misc::GameObject*> heartIcons;
	misc::GameObject *pauseButton;
	misc::Timer inputTimer;
	glm::vec2 touchPosition;
};

#endif // GAMEUI_H