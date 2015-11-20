#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "../engine/misc/GameObject.h"

#include "Scene.hpp"

class LevelSelect : public Scene
{
public:
	LevelSelect();
	~LevelSelect();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box);

private:
	bool lvl2Unlocked = true;
	bool lvl3Unlocked = true;
	bool bosslvlUnlocked = true;

	int boxSizey;
	int boxSizex;

	misc::GameObject *plainsLevel;
	misc::GameObject *forestLevel;
	misc::GameObject *castleLevel;
	misc::GameObject *bossLevel;
};

#endif // LEVELSELECT_H