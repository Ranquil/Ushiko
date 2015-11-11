#ifndef CASTLEGENERATOR_H
#define CASTLEGENERATOR_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

#include "Enemy.hpp"

struct Tile
{
	Tile(misc::GameObject *t, int x, int y) :
		go(t), xPos(x), yPos(y) {}
	~Tile() { delete go; }
	misc::GameObject *go;
	int xPos, yPos;
};

class CastleGenerator
{
public:
	CastleGenerator(core::Siika2D *siika);
	~CastleGenerator();

	void update(core::Siika2D *siika);

private:
	void spawnTile(core::Siika2D *siika, int xPos, int yPos);

	bool platformHasEnemy;
	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;

	std::vector<Tile*> tiles;
	std::vector<Enemy*> enemies;
};

#endif // CASTLEGENERATOR_H