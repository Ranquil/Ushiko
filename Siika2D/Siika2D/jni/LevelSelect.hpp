#ifndef LEVELSELECT
#define LEVELSELECT
#include "Scene.hpp"

class LevelSelect : public Scene
{
public:
	LevelSelect();
	~LevelSelect();

	virtual int update(core::Siika2D *siika);
};


#endif //LEVELSELECT