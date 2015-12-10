#include "LevelGenerator.hpp"
#include "Ushiko.hpp"
#include "Sound.hpp"

LevelGenerator::LevelGenerator(core::Siika2D *siika, std::string name)
{
	srand48(time(NULL));

	tiles.clear();
	enemies.clear();
	collectables.clear();
	puffs.clear();

	tileMovement = 0;
	platformLength = 10;
	platformSpawned = 0;
	platformHasEnemy = false;
	generatorName = name;
	platformNum = 0;

	yLevel = siika->_graphicsContext->getDisplaySize().y * 2 + 400;
	ushiko.groundLevel = yLevel;

	// Go through update a few times to spawn the starting platform.
	// This slows down loading just a little bit, so TODO(Jere):
	// change this to spawn the platform without using update().
	for (int i = 0; i < 250; i++)
		update(siika);
}

LevelGenerator::~LevelGenerator()
{
	for (Tile *t : tiles)
		delete t;
	for (Enemy *e : enemies)
		delete e;
	for (Collectable *c : collectables)
		delete c;
	for (Puff *p : puffs)
		delete p;

	tiles.clear();
	enemies.clear();
	collectables.clear();
	puffs.clear();
}

double distance(glm::vec2 go1, glm::vec2 go2)
{
	return sqrt((go2.x-go1.x) * (go2.x-go1.x) + (go2.y-go1.y) * (go2.y-go1.y));
}

void LevelGenerator::update(core::Siika2D *siika)
{
	glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());

	ushikoPos.x += 100;
	ushikoPos.y = -ushikoPos.y;

	// Ushiko has fallen and can't get up
	if (ushikoPos.y < -siika->_graphicsContext->getDisplaySize().y * 3)
	{
		ushiko.health -= ushiko.healthMax;
		sound.playSound(KUOLONKORINA);
		return;
	}

	updateTiles(ushikoPos);
	updateCollectables(ushikoPos);
	updatePuffs(siika);

	/* ----- SPAWNING TILES & ENEMIES ----- */

	updateEnemies(siika, ushikoPos);

	tileMovement += 1;
	if (tileMovement >= 14)
	{
		tileMovement = 0;

		glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
		if (platformSpawned < platformLength)
		{
			spawnTile(siika, screenSize.x * 1.8, -yLevel);
			platformSpawned += 1;

			// 25% chance (per tile) to spawn an enemy on a tile past the half-way point of the platform
			if (!platformHasEnemy && platformSpawned > (int)(platformLength / 2) &&
				platformSpawned != platformLength && lrand48() % 4 == 0 &&
				generatorName != "boss")
			{
				spawnEnemy(siika, screenSize.x * 1.8, -yLevel + 240);
				platformHasEnemy = true;
			}

			// Spawn a coin on every 4th platform, starting from 3rd platform (#2)
			if (platformNum == 2 && platformSpawned == (int)(platformLength / 2) - 1)
			{
				spawnCollectable(siika, screenSize.x * 1.8, -yLevel + 220);
			}
		}
		else
		{
			platformLength = lrand48() % 10;
			if (generatorName == "forest")
				platformLength += 4;
			else if (generatorName == "castle" || generatorName == "boss")
				platformLength += 2;
			else platformLength += 6;

			platformSpawned = 0;
			platformHasEnemy = false;

			platformNum += 1;
			if (platformNum > 3) // Platforms are #0-3
				platformNum = 0;

			int previousY = yLevel;
			while (yLevel == previousY)
			{
				// Change the (Y) level of the new platform
				yLevel = lrand48() % 3;
				switch (yLevel)
				{
					case 0: yLevel = 580; break;
					case 1: yLevel = screenSize.y * 2 - 240; break;
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
	else if (generatorName == "castle" || generatorName == "boss")
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
	sprtComp->setZ(80);

	t->addComponent(trnsComp);
	t->addComponent(sprtComp);
	t->move(pos);

	Tile *newTile = new Tile(t, xPos, yPos);
	tiles.push_back(newTile);
}

void LevelGenerator::spawnEnemy(core::Siika2D *siika, int xPos, int yPos)
{
	Enemy *e;
	bool fly = false;
	if (lrand48() % 3 == 0)
		fly = true;

	int frames = 0;
	int speed = 200;

	if (fly)
	{
		if (generatorName == "castle")
			e = new Enemy("sprite_mikucopter.png");
		else if (generatorName == "plains")
			e = new Enemy("sprite_noodles.png");
		else
		{
			e = new Enemy("sprite_shibat.png");
			yPos += 80;
		}
	}
	else
	{
		if (generatorName == "castle")
			e = new Enemy("sprite_meido.png");
		else if (generatorName == "forest")
			e = new Enemy("sprite_shimapanda.png");
		else
		{
			e = new Enemy("sprite_gigapuddi.png", true);
			speed = 100;
			frames = 8;
		}
	}

	e->init(siika, 0, frames, speed);
	e->xPos = xPos;
	e->yPos = yPos;
	e->yLevel = e->yPos;

	if (fly)
		e->flies = true;

	e->go->move(glm::vec2(e->xPos, e->yPos));

	enemies.push_back(e);
}

void LevelGenerator::spawnCollectable(core::Siika2D *siika, int xPos, int yPos)
{
	Collectable *c = new Collectable;
	if (generatorName == "boss")
		c->init(siika, true);
	else c->init(siika);

	c->xPos = xPos;
	c->yPos = yPos;
	c->go->move(glm::vec2(c->xPos, c->yPos));

	collectables.push_back(c);
}

void LevelGenerator::updateTiles(glm::vec2 ushikoPos)
{
	int tileAmount = 0;
	bool deleteTile = false;

	for (Tile *t : tiles)
	{
		t->go->update();
		t->go->move(glm::vec2(t->xPos -= 7, t->yPos));

		if (t->xPos < ushikoPos.x + 10 && t->xPos > ushikoPos.x - 10)
			ushiko.groundLevel = -t->yPos;

		// When there are over 30 tiles, destroy the oldest
		tileAmount += 1;
		if (tileAmount > 30)
			deleteTile = true;
	}

	if (deleteTile)
	{
		Tile *t = tiles.front();
		tiles.erase(tiles.begin());
		delete t;
	}
}

void LevelGenerator::updateEnemies(core::Siika2D *siika, glm::vec2 ushikoPos)
{
	Enemy *eDelete = nullptr;
	for (Enemy *e : enemies)
	{
		int enemyXpos = siika->transfCrds()->deviceToUser(e->go->getComponent<misc::TransformComponent>()->getPosition()).x;

		e->update(siika);
		e->go->move(glm::vec2(e->flies ? e->xPos -= 10 : e->xPos -= 7, e->yPos));

		if (e->flies)
		{
			if (e->rising)
			{
				e->go->move(glm::vec2(e->xPos, e->yPos -= 2));
				if (e->yPos < e->yLevel - 12)
					e->rising = false;
			}
			else
			{
				e->go->move(glm::vec2(e->xPos, e->yPos += 2));
				if (e->yPos > e->yLevel + 12)
					e->rising = true;
			}
		}

		// Hit or get git by Ushiko, if colliding with her
		if (!e->hasHit &&
			e->xPos < ushikoPos.x && e->xPos > ushikoPos.x - 100 &&
			e->yPos < ushikoPos.y + 200 && e->yPos > ushikoPos.y - 200)
		{
			if (ushiko.dashing)
			{
				eDelete = e;
				if (!e->flies)
					ushiko.pointsAmount += 20;
				else ushiko.pointsAmount += 40;

				ushiko.enemiesKilled += 1;

				Puff *p = new Puff;
				p->init(siika, e->xPos, e->yPos);
				puffs.push_back(p);

				sound.playSound(ENEMY_DEAD);
			}
			else
			{
				ushiko.health -= 1;
				if (ushiko.health > 0)
					sound.playSound(USHIKO_HURT);
				else sound.playSound(KUOLONKORINA);
			}
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
}

void LevelGenerator::updateCollectables(glm::vec2 ushikoPos)
{
	Collectable *cDelete = nullptr;
	for (Collectable *c : collectables)
	{
		c->go->update();

		glm::vec2 ushikoPosition = ushiko.go->getComponent<misc::TransformComponent>()->getPosition();
		if (distance(c->go->getComponent<misc::TransformComponent>()->getPosition(), ushikoPosition) < 50)
		{
			if (c->isHeart == false)
			{
				if (ushiko.coinCount < ushiko.maxCoins)
					ushiko.coinCount += 1;

				switch (c->coinType)
				{
					case BRONZE: ushiko.pointsAmount += 10; break;
					case SILVER: ushiko.pointsAmount += 50; break;
					case GOLD: ushiko.pointsAmount += 150; break;
					default: break;
				}
			}
			else
			{
				if (ushiko.health < ushiko.healthMax)
					ushiko.health += 1;
			}
			cDelete = c;
		}

		c->update();
		c->go->move(glm::vec2(c->xPos -= 7, c->yPos));

		if (c->xPos < -100)
			cDelete = c;
	}

	if (cDelete != nullptr)
	{
		for (int i = 0; i < collectables.size(); i++)
		{
			if (collectables[i] == cDelete)
			{
				collectables.erase(collectables.begin() + i);
				break;
			}
		}
		delete cDelete;
	}
}

void LevelGenerator::updatePuffs(core::Siika2D *siika)
{
	Puff *pDelete = nullptr;
	for (Puff *p : puffs)
	{
		if (p->go != NULL)
		{
			p->go->move(glm::vec2(p->xPos -= 7, p->yPos));
			p->update(siika);
		}
		else pDelete = p;
	}
	if (pDelete != nullptr)
	{
		for (int i = 0; i < puffs.size(); i++)
		{
			if (puffs[i] = pDelete)
			{
				puffs.erase(puffs.begin() + i);
				break;
			}
		}
		delete pDelete;
	}
}

//void LevelGenerator::heartsplode(core::Siika2D *siika, int x, int y)
//{
//	for (Heartsplosion *heart : hearts)
//		delete heart;
//	hearts.clear();
//
//	for (int i = 0; i < 10; i++)
//	{
//		Heartsplosion *heart = new Heartsplosion;
//		heart->init(siika, x, y);
//		heart->xPos = x;
//		heart->yPos = y;
//		heart->go->move(glm::vec2(x, y));
//		hearts.push_back(heart);
//	}
//}