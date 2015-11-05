#ifndef GAMEUI
#define GAMEUI

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
private:
	LevelTimer *lt;

};


#endif //GAMEUI