#ifndef LEVELGENERATOR
#define LEVELGENERATOR

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

struct Tile
{
	Tile(misc::GameObject *t, int yPos)
	{
		this->tile = t;
		this->yLevel = yPos;
	}
	misc::GameObject *tile;
	int yLevel;
};

class LevelGenerator
{
public:
	LevelGenerator(core::Siika2D *siika);
	~LevelGenerator();

	void update(core::Siika2D *siika);

	misc::Timer generatorTimer;

private:
	std::vector<Tile*> tiles;

	void spawnTile(core::Siika2D *siika, int xPos, int yPos);

	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;
};

#endif // LEVELGENERATOR