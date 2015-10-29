#include "Level.hpp"
#include "GlobalVariables.hpp"

Level::Level(core::Siika2D *siika)
{
	graphics::Texture *ushikoTexture = siika->_textureManager->createTexture("erg.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
																glm::vec2(0, 0), 
																glm::vec2(128, 128), 
																glm::vec2(64, 64), 
																ushikoTexture, 
																glm::vec2(0, 0), 
																glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;
	misc::PhysicsComponent *physicsComp = new misc::PhysicsComponent;

	ushiko.addComponent(transComp);
	ushiko.addComponent(sprtComp);
	ushiko.addComponent(physicsComp);

	ushiko.move(glm::vec2(200, 100));

	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));

	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	lg = new LevelGenerator(siika);
}

Level::~Level()
{

}

int Level::update(core::Siika2D *siika)
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
		ushiko.move(position);
	}

	siika->_boxWorld->Step(1.f / 60.f, 6, 2);
	siika->_graphicsContext->clear();

	ushiko.update();

	if (lg->generatorTimer.getElapsedTime(MILLISECONDS) > 10)
	{
		lg->generatorTimer.reset();
		lg->update(siika);
	}

	lt->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return GAME_LEVEL;
}