#ifndef LEVELSELECT
#define LEVELSELECT
#include "Scene.hpp"

class LevelSelect : public Scene
{
public:
	LevelSelect();
	~LevelSelect();

	virtual void init(core::Siika2D *siika);
	virtual void deInit(core::Siika2D *siika);

	virtual int update(core::Siika2D *siika);

	misc::GameObject plainsLevel;
	misc::GameObject forestLevel;
	misc::GameObject castleLevel;
};


#endif //LEVELSELECT