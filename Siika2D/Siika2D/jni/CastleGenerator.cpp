#include "CastleGenerator.hpp"
#include "Scene.hpp"

CastleGenerator::CastleGenerator(core::Siika2D *siika)
{
	tiles.clear();
	generatorTimer.start();

	srand48(time(NULL));

	tileMovement = 0;
	platformLength = 10;
	platformSpawned = 0;

	yLevel = siika->_graphicsContext->getDisplaySize().y * 2 + 400;
}

CastleGenerator::~CastleGenerator()
{
	tiles.clear();
}

void CastleGenerator::update(core::Siika2D *siika)
{
	int tileAmount = 0;
	bool deleteTile = false;

	tileMovement += 1;
	for (Tile *t : tiles)
	{
		t->go->update();
		t->go->move(glm::vec2(t->xPos -= 4, t->yPos));

		tileAmount += 1;
		if (tileAmount > 42)
			deleteTile = true;
	}

	if (deleteTile)
		tiles.erase(tiles.begin());

	if (tileMovement >= 16)
	{
		tileMovement = 0;

		glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
		if (platformSpawned < platformLength)
		{
			int x = screenSize.x * 2;
			spawnTile(siika, x, -yLevel);
			platformSpawned += 1;
		}
		else
		{
			platformSpawned = 0;
			platformLength = mrand48() % 10 + 7;
			int previousY = yLevel;
			while (yLevel == previousY)
			{
				yLevel = mrand48() % 3;
				switch (yLevel)
				{
					case 0: yLevel = 400; break;
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

	misc::GameObject *t = new misc::GameObject(pos, siika->_textureManager->createTexture(textureName), glm::vec2(64, 64), glm::vec2(32, 32));
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		pos,
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		siika->_textureManager->createTexture(textureName),
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	t->removeComponent<misc::SpriteComponent>();
	sprtComp->setZ(80);

	t->addComponent(sprtComp);

	t->getComponent<misc::PhysicsComponent>()->setSize(glm::vec2(32, 32));
//	t->getComponent<misc::PhysicsComponent>()->setGravityScale(0);
	t->move(pos);

	t->setId(GROUND);

	Tile *newTile = new Tile(t, xPos, yPos);
	tiles.push_back(newTile);
}