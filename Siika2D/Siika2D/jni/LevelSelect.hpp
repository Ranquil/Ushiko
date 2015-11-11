#ifndef LEVELSELECT_H
#define LEVELSELECT_H

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
	bool lvl2Unlocked = false;
	bool lvl3Unlocked = false;
	int boxSizey;
	int boxSizex;

	misc::GameObject *plainsLevel;
	misc::GameObject *forestLevel;
	misc::GameObject *castleLevel;
};


#endif // LEVELSELECT_H