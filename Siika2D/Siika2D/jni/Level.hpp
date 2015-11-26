#ifndef LEVEL_H
#define LEVEL_H

//#include "../engine/audio/Audio.h"

#include "Scene.hpp"
#include "LevelGenerator.hpp"
#include "GameUI.hpp"
#include "Boss.hpp"

class Level : public Scene
{
public:
	Level(std::string name);
	~Level();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual void pause();
	virtual void resume();

private:
	bool paused;
	bool unlocked;
	std::string levelName;

	LevelGenerator *lg;
	GameUI *gameUI;

	misc::Timer genTimer;
	audio::Audio *theme;
	audio::Audio *coin;
	Boss *boss;
};

#endif // LEVEL_H