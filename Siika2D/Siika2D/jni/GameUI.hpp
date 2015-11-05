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

	void init(core::Siika2D *siika);

	void deInit();

	int update(core::Siika2D *siika);

	int gemCount;
	const int maxGems = 20;
	graphics::Text *gemTextUI;
	misc::GameObject *pauseButton;
	glm::vec2 touchPosition;
private:
	LevelTimer *lt;

};


#endif //GAMEUI