#include "Ushiko.hpp"
#include "Scene.hpp"

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
	misc::PhysicsComponent *physComp = new misc::PhysicsComponent(glm::vec2(0, 0), glm::vec2(1, 1));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	go->addComponent(sprtComp);
	go->addComponent(physComp);
	go->addComponent(trnsComp);

	sprtComp->setZ(10);
	go->setId(USHIKO);
	go->move(glm::vec2(-1000, 0));

	tempTimer.start();
	canJump = true;
}

void Ushiko::update(core::Siika2D *siika, colListener *collisions)
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

	go->update();

	std::vector<misc::GameObject*> *cols = nullptr;
	if (cols = collisions->getCollisionsFor(go))
	{
		for (misc::GameObject *g : *cols)
		{
			if (g->getId() == GROUND)
			{
				ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
				cols->clear();
			}
		}
	}

	if (!canJump && tempTimer.getElapsedTime(MILLISECONDS) > 600)
		canJump = true;
}