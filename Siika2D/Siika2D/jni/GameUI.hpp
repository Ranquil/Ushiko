#ifndef GAMEUI_H
#define GAMEUI_H

#include "LevelTimer.hpp"

class GameUI
{
public:
	GameUI();
	~GameUI();

	void init(core::Siika2D *siika);

	void deInit();

	void update(core::Siika2D *siika);

	int gemCount;
	const int maxGems = 20;
	graphics::Text *gemTextUI;
private:
	LevelTimer *lt;

};


#endif //GAMEUI