#include "Castle.hpp"

Castle::Castle()
{

}

Castle::~Castle()
{

}

void Castle::init(core::Siika2D *siika)
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

	sprtComp->setZ(10);

	ushiko.addComponent(transComp);
	ushiko.addComponent(sprtComp);
	ushiko.addComponent(physicsComp);

	ushiko.move(glm::vec2(200, 100));

	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));

	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	lg = new CastleGenerator(siika);

	canJump = true;
	ushiko.getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(5, 0));
}

void Castle::deInit(core::Siika2D *siika)
{

}

int Castle::update(core::Siika2D *siika)
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		//position = siika->_input->touchPosition(i)._positionCurrent;

		if (canJump) {
			ushiko.getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			ushiko.getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 40), false);
			tempTimer.reset();
			canJump = false;
		}
	}

	if (!canJump && tempTimer.getElapsedTime(MILLISECONDS) > 600) {
		canJump = true;
	}

	std::vector<misc::GameObject*> *cols = nullptr;
	if (cols = collisionListener.getCollisionsFor(&ushiko))
	{
		if (!cols->empty())
		{
			ushiko.getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			cols->clear();
		}
	}

	siika->_boxWorld->Step(1.5f / 60.0f, 6, 2);
	siika->_graphicsContext->clear();

	if (lg->generatorTimer.getElapsedTime(MILLISECONDS) > 10)
	{
		lg->generatorTimer.reset();
		lg->update(siika);
	}

	ushiko.update();
	lt->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return CASTLE_LEVEL;
}