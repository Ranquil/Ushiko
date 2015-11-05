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

	int gemCount;
	const int maxGems = 20;

	graphics::Text *gemTextUI;
	graphics::Sprite *shade;

	misc::GameObject *pauseButton;
	glm::vec2 touchPosition;

	UIState lastState;

private:
	LevelTimer *lt;
	misc::Timer inputTimer;
};


#endif //GAMEUI