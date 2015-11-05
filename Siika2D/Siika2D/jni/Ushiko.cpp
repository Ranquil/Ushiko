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

	go->addComponent(trnsComp);
	go->addComponent(sprtComp);
	go->addComponent(physComp);

	sprtComp->setZ(10);
	go->setId(USHIKO);
	go->move(glm::vec2(-1000, 0));

	doubleJump = false;
	canJump = true;
}

void Ushiko::update(core::Siika2D *siika, colListener *collisions)
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		if (canJump || !doubleJump)
		{
			ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 35), false);

			if (canJump)
				canJump = false;
			else if (!doubleJump)
				doubleJump = true;
		}
	}
	int ushikoLevel = siika->transfCrds()->deviceToUser(go->getComponent<misc::TransformComponent>()->getPosition()).y;
	if (ushikoLevel > groundLevel - 250 && ushikoLevel < groundLevel && go->getComponent<misc::PhysicsComponent>()->_body->GetLinearVelocity().y < -1)
	{
		ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
		ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 5), false);

		doubleJump = false;
		canJump = true;
	}
	/*
	std::vector<misc::GameObject*> *cols = nullptr;
	if (cols = collisions->getCollisionsFor(ushiko.go))
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
	//*/

	go->update();
}