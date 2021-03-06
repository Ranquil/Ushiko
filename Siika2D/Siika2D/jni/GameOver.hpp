#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Scene.hpp"

#include "../engine/misc/GameObject.h"

class GameOver : public Scene
{
public:
	GameOver();
	~GameOver();

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual int update(core::Siika2D *siika);

private:
	graphics::Sprite *gameOver;
	graphics::Sprite *deadUshiko;
	int deathSteps;
	int deathFrames;

	graphics::Text *enemiesText;
	//graphics::Text *scoreText;
};

#endif // GAME_OVER_H