#include "LevelGenerator.hpp"

//#include <sstream>

LevelGenerator::LevelGenerator(core::Siika2D *siika)
{
	tiles.clear();
	generatorTimer.start();

	srand48(time(NULL));

/*	text = siika->_textManager->createText();
	text->setPosition(-1, 0.8);
	text->setFont("arial.ttf");
	text->setText("Tiles: 0");
*/
	platformLength = 10;
	platformSpawned = 0;
	yLevel = siika->_graphicsContext->getDisplaySize().y / 2 + 72;
}

LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::update(core::Siika2D *siika)
{
	int tileAmount = 0;
	bool deleteTile = false;

	for (misc::GameObject *t : tiles)
	{
		glm::vec2 tPos = t->getComponent<misc::TransformComponent>()->getPosition();
		t->getComponent<misc::TransformComponent>()->setPosition(glm::vec2(tPos.x - 5, tPos.y));
		t->update();

		tileAmount += 1;
		if (tileAmount > 42)
			deleteTile = true;
	}

	if (deleteTile)
	{
		tiles.erase(tiles.begin());
	}

/*	std::ostringstream ttt;
	ttt << "Tiles: " << tileAmount;
	text->setText(ttt.str());
*/
	if (generatorTimer.getElapsedTime(TIME::SECONDS) > 0.18f)
	{
		generatorTimer.reset();

		glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
		if (platformSpawned < platformLength)
		{
			int x = screenSize.x;
			spawnTile(siika, x, yLevel);
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
					case 0: yLevel = 196; break;
					case 1: yLevel = screenSize.y - 32; break;
					default: yLevel = screenSize.y / 2 + 72; break;
				}
			}
		}
	}
}

void LevelGenerator::spawnTile(core::Siika2D *siika, int xPos, int yPos)
{
	misc::GameObject *t = new misc::GameObject;

	std::string textureName = "tile_grass_middle.png";
	if (platformSpawned == 0)
		textureName = "tile_grass_left_corner.png";
	else if (platformSpawned == platformLength - 1)
		textureName = "tile_grass_right_corner.png";

	misc::SpriteComponent *spriteComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(-100, 0), glm::vec2(64, 64), glm::vec2(32, 32), siika->_textureManager->createTexture(textureName), glm::vec2(0, 0), glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent();
	transComp->setPosition(glm::vec2(xPos, yPos));

	t->addComponent(spriteComp);
	t->addComponent(transComp);

	tiles.push_back(t);
}