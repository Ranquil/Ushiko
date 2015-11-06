#include "CastleGenerator.hpp"
#include "Scene.hpp"

#include "Ushiko.hpp"

CastleGenerator::CastleGenerator(core::Siika2D *siika)
{
	tiles.clear();
	enemies.clear();

	srand48(time(NULL));

	tileMovement = 0;
	platformLength = 10;
	platformSpawned = 0;
	platformHasEnemy = false;

	yLevel = siika->_graphicsContext->getDisplaySize().y * 2 + 400;
	ushiko.groundLevel = yLevel;

	for (int i = 0; i < 280; i++)
		update(siika);
}

CastleGenerator::~CastleGenerator()
{
	for (Tile *t : tiles)
		delete t;
	for (Enemy *e : enemies)
		delete e;

	tiles.clear();
	enemies.clear();
}

void CastleGenerator::update(core::Siika2D *siika)
{
	int tileAmount = 0;
	bool deleteTile = false;

	glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
	ushikoPos.x += 100;
	ushikoPos.y = -ushikoPos.y;

	if (ushikoPos.y < -siika->_graphicsContext->getDisplaySize().y * 3)
	{
		ushiko.health -= ushiko.healthMax;
		return;
	}

	tileMovement += 1;
	for (Tile *t : tiles)
	{
		t->go->update();
		t->go->move(glm::vec2(t->xPos -= 5, t->yPos));

		if (t->xPos < ushikoPos.x && t->xPos > ushikoPos.x - 10)
			ushiko.groundLevel = -t->yPos;

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

	bool deleteEnemy = false;
	for (Enemy *e : enemies)
	{
		int enemyXpos = siika->transfCrds()->deviceToUser(e->go->getComponent<misc::TransformComponent>()->getPosition()).x;

		e->update(siika);
		e->go->move(glm::vec2(e->xPos -= 5, e->yPos));

		if (!e->hasHit &&
			e->xPos < ushikoPos.x && e->xPos > ushikoPos.x - 100 &&
			e->yPos < ushikoPos.y + 200 && e->yPos > ushikoPos.y - 200)
		{
			if (ushiko.dashing)
				deleteEnemy = true;
			else ushiko.health -= 1;

			e->hasHit = true;
		}

		if (enemyXpos <= 0)
			deleteEnemy = true;
	}

	if (deleteEnemy)
	{
		Enemy *e = enemies.front();
		enemies.erase(enemies.begin());
		delete e;
	}

	if (tileMovement >= 17)
	{
		tileMovement = 0;

		glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
		if (platformSpawned < platformLength)
		{
			spawnTile(siika, screenSize.x * 1.6f, -yLevel);
			platformSpawned += 1;

			if (!platformHasEnemy && platformSpawned > (int)(platformLength / 2) && mrand48() % 4 == 0)
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
				yLevel = mrand48() % 3;
				switch (yLevel)
				{
					case 0: yLevel = 450; break;
					case 1: yLevel = screenSize.y * 2 - 300; break;
					default: yLevel = screenSize.y * 2 + 400; break;
				}
			}
		}
	}
}

void CastleGenerator::spawnTile(core::Siika2D *siika, int xPos, int yPos)
{
	std::string textureName = "tile_castle_middle.png";
	if (platformSpawned == 0)
		textureName = "tile_castle_left.png";
	else if (platformSpawned == platformLength - 1)
		textureName = "tile_castle_right.png";

	glm::vec2 pos = glm::vec2(xPos, yPos);

	misc::GameObject *t = new misc::GameObject;
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		pos,
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		siika->_textureManager->createTexture(textureName),
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
//	misc::PhysicsComponent *physComp = new misc::PhysicsComponent(pos, glm::vec2(64, 64));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	t->addComponent(trnsComp);
	t->addComponent(sprtComp);
//	t->addComponent(physComp);

	sprtComp->setZ(80);
	t->setId(GROUND);
	t->move(pos);

	Tile *newTile = new Tile(t, xPos, yPos);
	tiles.push_back(newTile);
}