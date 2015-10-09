#ifndef LEVELTIMER
#define LEVELTIMER

#include "../engine/misc/timer.h"
#include "../engine/core/Siika2D.h"
#include <sstream>

class LevelTimer
{
public:
	LevelTimer();
	~LevelTimer();

	void InitTimer(core::Siika2D *siika, std::string fontName, int fontSize, float xPosition, float yPosition);

	void update();
private:
	misc::Timer levelTimer;
	int timerMinutes;
	graphics::Text *levelTimerText;
};

#endif