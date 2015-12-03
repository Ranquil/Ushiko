#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Scene.hpp"

#include "../engine/misc/GameObject.h"

class LevelSelect : public Scene
{
public:
	LevelSelect();
	~LevelSelect();

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual int update(core::Siika2D *siika);

private:
	bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box);
	std::vector<misc::GameObject*> levelLocks;

	int unlocked;
	int boxSizey, boxSizex;

	misc::GameObject *plainsLevel;
	misc::GameObject *forestLevel;
	misc::GameObject *castleLevel;
	misc::GameObject *bossLevel;
};

#endif // LEVELSELECT_H