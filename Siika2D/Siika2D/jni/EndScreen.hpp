#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include "Scene.hpp"

class EndScreen : public Scene
{
public:
	EndScreen();
	~EndScreen();

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual int update(core::Siika2D *siika);
private:
	graphics::Sprite *endScreen;

};

#endif