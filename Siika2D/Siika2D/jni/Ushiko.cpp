#include "Ushiko.hpp"

Ushiko ushiko;

Ushiko::Ushiko()
{

}

Ushiko::~Ushiko()
{

}

void Ushiko::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

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

	go->addComponent(transComp);
	go->addComponent(sprtComp);
	go->addComponent(physicsComp);

	tempTimer.start();
	canJump = true;

	go->setId(USHIKO);
}

void Ushiko::update(core::Siika2D *siika)
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		if (canJump)
		{
			ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 35), false);
			tempTimer.reset();
			canJump = false;
		}
	}

	if (!canJump && tempTimer.getElapsedTime(MILLISECONDS) > 600)
		canJump = true;

	go->update();
}