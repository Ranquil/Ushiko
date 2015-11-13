#include "LevelGenerator.hpp"
#include "Ushiko.hpp"

// TODO(Jere): remove this file when we have generators for different levels

LevelGenerator::LevelGenerator(core::Siika2D *siika, std::string name)
{
	tiles.clear();
	enemies.clear();

	srand48(time(NULL));

	tileMovement = 0;
	platformLength = 10;
	platformSpawned = 0;
	platformHasEnemy = false;
	generatorName = name;

	yLevel = siika->_graphicsContext->getDisplaySize().y * 2 + 400;
	ushiko.groundLevel = yLevel;

	// Go through update a few times to spawn the starting platform.
	// This slows down loading just a little bit, so TODO(Jere):
	// change this to spawn the platform without using update().
	for (int i = 0; i < 280; i++)
		update(siika);
}

LevelGenerator::~LevelGenerator()
{
	for (Tile *t : tiles)
		delete t;
	for (Enemy *e : enemies)
		delete e;

	tiles.clear();
	enemies.clear();
}

void LevelGenerator::update(core::Siika2D *siika)
{
	int tileAmount = 0;
	bool deleteTile = false;

	glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
	ushikoPos.x += 100;
	ushikoPos.y = -ushikoPos.y;

	// Ushiko has fallen from the screen
	if (ushikoPos.y < -siika->_graphicsContext->getDisplaySize().y * 3)
	{
		ushiko.health -= ushiko.healthMax;
		return;
	}

	/* ----- UPDATING TILES ----- */

	for (Tile *t : tiles)
	{
		t->go->update();
		t->go->move(glm::vec2(t->xPos -= 5, t->yPos));

		if (t->xPos < ushikoPos.x && t->xPos > ushikoPos.x - 10)
			ushiko.groundLevel = -t->yPos;

		// When there are over 24 tiles, destroy the oldest
		tileAmount += 1;
		if (tileAmount > 24)
			deleteTile = true;
	}

	if (deleteTile)
	{
		Tile *t = tiles.front();
		tiles.erase(tiles.begin());
		delete t;
	}

	/* ----- UPDATING ENEMIES ----- */

	Enemy *eDelete = nullptr;
	for (Enemy *e : enemies)
	{
		int enemyXpos = siika->transfCrds()->deviceToUser(e->go->getComponent<misc::TransformComponent>()->getPosition()).x;

		e->update(siika);
		e->go->move(glm::vec2(e->xPos -= 5, e->yPos));

		// Hit or get git by Ushiko, if colliding with her
		if (!e->hasHit &&
			e->xPos < ushikoPos.x && e->xPos > ushikoPos.x - 100 &&
			e->yPos < ushikoPos.y + 200 && e->yPos > ushikoPos.y - 200)
		{
			if (ushiko.dashing)
				eDelete = e;
			else ushiko.health -= 1;

			e->hasHit = true;
		}

		if (enemyXpos <= -100)
			eDelete = e;
	}

	if (eDelete != nullptr)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i] == eDelete)
			{
				enemies.erase(enemies.begin() + i);
				break;
			}
		}
		delete eDelete;
	}

	/* ----- SPAWNING TILES & ENEMIES ----- */

	tileMovement += 1;
	if (tileMovement >= 18)
	{
		tileMovement = 0;

		glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
		if (platformSpawned < platformLength)
		{
			spawnTile(siika, screenSize.x * 1.6f, -yLevel);
			platformSpawned += 1;

			// 25% chance (per tile) to spawn an enemy on a tile past the half-way point of the platform
			if (!platformHasEnemy && platformSpawned >(int)(platformLength / 2) && mrand48() % 4 == 0)
			{
				Enemy *e = new Enemy("sprite_shimapanda.png");

				e->init(siika);
				e->xPos = screenSize.x * 1.6f;
				e->yPos = -yLevel + 200;
				e->go->move(glm::vec2(e->xPos, e->yPos));

				enemies.push_back(e);
				platformHasEnemy = true;
			}
		}
		else
		{
			platformSpawned = 0;
			platformLength = mrand48() % 10 + 5;
			platformHasEnemy = false;

			int previousY = yLevel;
			while (yLevel == previousY)
			{
				// Change the (Y) level of the new platform
				yLevel = mrand48() % 3;
				switch (yLevel)
				{
				case 0: yLevel = 550; break;
				case 1: yLevel = screenSize.y * 2 - 275; break;
				default: yLevel = screenSize.y * 2 + 400; break;
				}
			}
		}
	}
}

void LevelGenerator::spawnTile(core::Siika2D *siika, int xPos, int yPos)
{
	std::string textureName = "tile_grass_middle.png";
	if (platformSpawned == 0)
		textureName = "tile_grass_left.png";
	else if (platformSpawned == platformLength - 1)
		textureName = "tile_grass_right.png";

	if (generatorName == "forest")
	{
		textureName = "tile_log_middle.png";
		if (platformSpawned == 0)
			textureName = "tile_log_left.png";
		else if (platformSpawned == platformLength - 1)
			textureName = "tile_log_right.png";
	}
	else if (generatorName == "castle")
	{
		textureName = "tile_castle_middle.png";
		if (platformSpawned == 0)
			textureName = "tile_castle_left.png";
		else if (platformSpawned == platformLength - 1)
			textureName = "tile_castle_right.png";
	}

	glm::vec2 pos = glm::vec2(xPos, yPos);

	misc::GameObject *t = new misc::GameObject;
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		pos,
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		siika->_textureManager->createTexture(textureName),
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	t->addComponent(trnsComp);
	t->addComponent(sprtComp);

	sprtComp->setZ(80);
	t->move(pos);

	Tile *newTile = new Tile(t, xPos, yPos);
	tiles.push_back(newTile);
}