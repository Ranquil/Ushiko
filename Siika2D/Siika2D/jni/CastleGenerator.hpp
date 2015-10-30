#ifndef CASTLEGENERATOR
#define CASTLEGENERATOR

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

class CastleGenerator
{
public:
	CastleGenerator(core::Siika2D *siika);
	~CastleGenerator();

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

#endif // CASTLEGENERATOR