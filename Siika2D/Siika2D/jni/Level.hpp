#ifndef LEVEL_H
#define LEVEL_H

#include "Scene.hpp"
#include "LevelGenerator.hpp"
#include "GameUI.hpp"

class Level : public Scene
{
public:
	Level(std::string name);
	~Level();

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual int update(core::Siika2D *siika);

	virtual void pause();
	virtual void resume();

private:
	bool paused;
	bool unlocked;

	LevelGenerator *lg;
	GameUI *gameUI;
	Boss *boss;

	std::string levelName;
	misc::Timer genTimer;
	audio::Audio *theme;
	audio::Audio *coin;
	graphics::Sprite *unlock;
	int unlockTimes;
};

#endif // LEVEL_H