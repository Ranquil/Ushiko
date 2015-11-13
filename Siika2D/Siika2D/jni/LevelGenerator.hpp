#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

#include "Enemy.hpp"
#include "Collectable.hpp"

struct Tile
{
	Tile(misc::GameObject *t, int x, int y) :
		go(t), xPos(x), yPos(y) {}
	~Tile() { delete go; }
	misc::GameObject *go;
	int xPos, yPos;
};

class LevelGenerator
{
public:
	LevelGenerator(core::Siika2D *siika, std::string name);
	~LevelGenerator();

	virtual void update(core::Siika2D *siika, bool timed = true);
	virtual void spawnTile(core::Siika2D *siika, int xPos, int yPos);

	bool platformHasEnemy;
	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;
	int platformNum;

	std::string generatorName;
	std::vector<Tile*> tiles;
	std::vector<Enemy*> enemies;
	std::vector<Collectable*> gems;

	misc::Timer genTimer;
};

#endif // LEVELGENERATOR_H