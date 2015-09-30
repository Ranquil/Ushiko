#include "LevelGenerator.hpp"

LevelGenerator::LevelGenerator()
{
	tiles.clear();
	generatorTimer.start();
}

LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::initSprites(core::Siika2D* siika, std::string texLeft, std::string texMiddle, std::string texRight)
{
	sprLeft = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(-100, 0), glm::vec2(64, 64), glm::vec2(32, 32), siika->_textureManager->createTexture(texLeft), glm::vec2(0, 0), glm::vec2(1, 1))));
	sprMiddle = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(-100, 0), glm::vec2(64, 64), glm::vec2(32, 32), siika->_textureManager->createTexture(texMiddle), glm::vec2(0, 0), glm::vec2(1, 1))));
	sprRight = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(-100, 0), glm::vec2(64, 64), glm::vec2(32, 32), siika->_textureManager->createTexture(texRight), glm::vec2(0, 0), glm::vec2(1, 1))));
}

int rng()
{
	return 1; // decided by fair dice roll
}

void LevelGenerator::update()
{
	for (misc::GameObject t : tiles)
		t.update();

	if (generatorTimer.getElapsedTime(TIME::SECONDS) > 2)
	{
		generatorTimer.reset();

		int x = 100; // need rng
		int y = 50;

		misc::GameObject t;
		misc::TransformComponent* transComp = new misc::TransformComponent();
		transComp->setPosition(glm::vec2(x, y));

		t.addComponent(sprMiddle);
		t.addComponent(transComp);

		tiles.push_back(t);
	}
}