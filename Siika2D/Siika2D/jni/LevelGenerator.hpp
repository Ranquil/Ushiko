#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "Enemy.hpp"
#include "Collectable.hpp"
#include "Puff.hpp"

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
	void spawnCollectable(core::Siika2D *siika, int xPos, int yPos);

	void updateTiles(glm::vec2 ushikoPos);
	void updateEnemies(core::Siika2D *siika, glm::vec2 ushikoPos);
	void updateCollectables(glm::vec2 ushikoPos);
	void updatePuffs(core::Siika2D *siika);

	bool platformHasEnemy;
	int tileMovement;
	int platformLength;
	int platformSpawned;
	int yLevel;
	int platformNum;

	std::string generatorName;
	std::vector<Tile*> tiles;
	std::vector<Enemy*> enemies;
	std::vector<Collectable*> collectables;
	std::vector<Puff*> puffs;
};

#endif // LEVELGENERATOR_H