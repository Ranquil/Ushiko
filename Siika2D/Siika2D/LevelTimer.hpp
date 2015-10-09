#ifndef LEVELTIMER
#define LEVELTIMER

#include "../engine/misc/timer.h"
#include "../engine/core/Siika2D.h"

class LevelTimer
{
public:
	LevelTimer();
	~LevelTimer();

	void InitTimer(core::Siika2D* siika);

private:
	misc::Timer levelTimer;
	int timerMinutes;
	graphics::Text *levelTimerText;
};

#endif