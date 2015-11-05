#ifndef LEVELTIMER_H
#define LEVELTIMER_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/timer.h"

class LevelTimer
{
public:
	LevelTimer();
	~LevelTimer();

	void update();
	void InitTimer(core::Siika2D *siika, std::string fontName, int fontSize, float xPosition, float yPosition);

private:
	int timerMinutes;

	misc::Timer levelTimer;
	graphics::Text *levelTimerText; 
};

#endif // LEVELTIMER_H