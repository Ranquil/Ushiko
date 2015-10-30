#include "Castle.hpp"
#include "Ushiko.hpp"

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::init(core::Siika2D *siika)
{
	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));

	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	lg = new CastleGenerator(siika);

	ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(5, 0));

	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	bg = siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("background_castle.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setSize(glm::vec2(scrSize.x, scrSize.y));
	bg->setZ(100);
}

void Castle::deInit(core::Siika2D *siika)
{
	delete lt, lg;
}

int Castle::update(core::Siika2D *siika)
{
	/*
	std::vector<misc::GameObject*> *cols = nullptr;
	if (cols = collisionListener.getCollisionsFor(ushiko.go))
	{
		if (!cols->empty())
		{
			ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			cols->clear();
		}
	}
	//*/

	siika->_boxWorld->Step(1.5f / 60.0f, 6, 2);
	siika->_graphicsContext->clear();

	if (lg->generatorTimer.getElapsedTime(MILLISECONDS) > 10)
	{
		lg->generatorTimer.reset();
		lg->update(siika);
	}

	ushiko.update(siika);
	lt->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return CASTLE_LEVEL;
}