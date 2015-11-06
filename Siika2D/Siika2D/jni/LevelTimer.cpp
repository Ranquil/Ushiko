#include "LevelTimer.hpp"

#include <sstream>

LevelTimer::LevelTimer()
{
	levelTimer.start();
	timerMinutes = 0;
}

LevelTimer::~LevelTimer()
{
	delete levelTimerText;
}

void LevelTimer::InitTimer(core::Siika2D *siika, std::string fontName, int fontSize, float xPosition, float yPosition)
{
	levelTimerText = siika->_textManager->createText();
	levelTimerText->setFont(fontName);
	levelTimerText->setPosition(xPosition, yPosition);
	levelTimerText->setFontSize(fontSize);
}

void LevelTimer::update()
{
	if (levelTimer.getElapsedTime(SECONDS) >= 60)
	{
		timerMinutes++;
		levelTimer.reset();
		
	}

	std::ostringstream timerOstring;
	timerOstring << timerMinutes << (levelTimer.getElapsedTime(SECONDS) < 10 ? ":0" : ":") << (int)levelTimer.getElapsedTime(SECONDS) << "/" << "2:00";
	levelTimerText->setText(timerOstring.str());
}