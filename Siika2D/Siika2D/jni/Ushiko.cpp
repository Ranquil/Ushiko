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

	jumpTimer.start();
	doubleJump = false;
	canJump = true;

	dashTimer.start();
	dashing = false;
	xOffset = 0;
}

void Ushiko::update(core::Siika2D *siika, colListener *collisions)
{
	if (xOffset > 0)
	{
		if (dashTimer.getElapsedTime(MILLISECONDS) > 100)
		{
			if (dashing)
			{
				xOffset += 5;

				if (xOffset > 50)
					dashing = false;
			}
			else
			{
				xOffset -= 5;
			}
			go->move(glm::vec2(xOrigin + xOffset, yOrigin));
		}
	}
	else
	{
		if (jumpTimer.getElapsedTime(MILLISECONDS) > 200 &&
			siika->_input->touchPositionsActive() > 0)
		{
			if (canJump || !doubleJump)
			{
				ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
				ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 35), false);

				if (canJump)
					canJump = false;
				else if (!doubleJump)
					doubleJump = true;

				jumpTimer.reset();
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
	}
	go->update();
}

void Ushiko::dash(core::Siika2D *siika)
{
	dashTimer.reset();
	dashing = true;
	xOffset = 1;
	glm::vec2 origin = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
	xOrigin = origin.x;
	yOrigin = origin.y;
}