#ifndef LEVELGENERATOR
#define LEVELGENERATOR

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

	void initSprites(core::Siika2D* siika, std::string texLeft, std::string texMiddle, std::string texRight);
	void update();

private:
	misc::Timer generatorTimer;
	misc::SpriteComponent *sprLeft, *sprMiddle, *sprRight;
	std::vector<misc::GameObject> tiles;
};

#endif // LEVELGENERATOR