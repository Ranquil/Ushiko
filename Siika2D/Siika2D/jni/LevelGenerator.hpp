#ifndef LEVELGENERATOR
#define LEVELGENERATOR

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

class LevelGenerator
{
public:
	LevelGenerator(core::Siika2D *siika);
	~LevelGenerator();

	void update(core::Siika2D *siika);

private:
	misc::Timer generatorTimer;
	std::vector<misc::GameObject*> tiles;

	void spawnTile(core::Siika2D *siika, int xPos, int yPos);

//	graphics::Text *text;

	int platformLength;
	int platformSpawned;
	int yLevel;
};

#endif // LEVELGENERATOR