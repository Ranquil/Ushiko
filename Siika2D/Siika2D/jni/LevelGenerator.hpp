#ifndef LEVELGENERATOR
#define LEVELGENERATOR

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

struct Tile
{
	Tile(misc::GameObject *t, int x, int y) :
		go(t), xPos(x), yPos(y) {}
	misc::GameObject *go;
	int xPos, yPos;
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

	graphics::Sprite *bg;

	void spawnTile(core::Siika2D *siika, int xPos, int yPos);

	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;
};

#endif // LEVELGENERATOR