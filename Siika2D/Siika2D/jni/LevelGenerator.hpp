#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"

#include "Enemy.hpp"
#include "Collectable.hpp"
#include "Heartsplosion.hpp"

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

	void update(core::Siika2D *siika);

private:
	void spawnTile(core::Siika2D *siika, int xPos, int yPos);
	void spawnEnemy(core::Siika2D *siika, int xPos, int yPos);
	void spawnCoin(core::Siika2D *siika, int xPos, int yPos);
	void heartsplode(core::Siika2D *siika, int xPos, int yPos);

	void updateTiles(glm::vec2 ushikoPos);
	void updateEnemies(core::Siika2D *siika, glm::vec2 ushikoPos);
	void updateCoins(glm::vec2 ushikoPos);

	bool platformHasEnemy;
	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;
	int platformNum;

	std::string generatorName;
	std::vector<Tile*> tiles;
	std::vector<Enemy*> enemies;
	std::vector<Collectable*> coins;
	std::vector<Heartsplosion*> hearts;
};

#endif // LEVELGENERATOR_H