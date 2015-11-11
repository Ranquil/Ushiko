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

	anim = IDLE;
	animTimer.start();

	graphics::Texture *ushikoTexture = siika->_textureManager->createTexture("sprite_ushiko.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		ushikoTexture,
		glm::vec2(0, 0),
		glm::vec2(0.2, 0.2))));
	misc::PhysicsComponent *physComp = new misc::PhysicsComponent;
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(10);

	go->addComponent(trnsComp);
	go->addComponent(sprtComp);
	go->addComponent(physComp);

	go->setId(USHIKO);
	go->move(glm::vec2(-1000, 0));

	health = healthMax;

	jumpTimer.start();
	doubleJump = true;
	canJump = false;

	dashTimer.start();
	dashing = false;
	xOffset = 0;
}

void Ushiko::update(core::Siika2D *siika)
{
	if (health > healthMax)
		health = healthMax;

	glm::vec2 touchPos = glm::vec2(0, 0);
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		touchPos = siika->_input->touchPosition(i)._positionStart;
		touchPos = siika->transfCrds()->deviceToUser(touchPos);
	}

	// Ushiko is dashing
	if (xOffset > 0)
	{
		ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
		if (dashTimer.getElapsedTime(MILLISECONDS) > 30)
		{
			if (dashing)
			{
				xOffset += 20;
				if (xOffset >= 200)
				{
					dashing = false;
					anim = RUN;
				}
			}
			else
			{
				xOffset -= 20;
				if (xOffset <= 0)
					xOffset = 0;
			}
			go->move(glm::vec2(originalPos.x + xOffset, -originalPos.y));
			dashTimer.reset();
		}
	}
	else
	{
		go->update();

		if (canJump || !doubleJump)
		{
			// Jump (tap on the left side of the screen)
			if (jumpTimer.getElapsedTime(SECONDS) > 0.2 && touchPos.x > 10 &&
				touchPos.x < siika->_graphicsContext->getDisplaySize().x / 2)
			{
				ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
				ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 35), false);

				if (canJump)
					canJump = false;
				else if (!doubleJump)
					doubleJump = true;

				jumpTimer.reset();
				anim = JUMP_START;
			}
			// Dash (tap on the right side of the screen)
			else if (xOffset <= 0 && dashTimer.getElapsedTime(SECONDS) > 1.8 &&
				touchPos.x > siika->_graphicsContext->getDisplaySize().x / 2)
			{
				if (xOffset <= 0)
				{
					dashing = true;
					xOffset = 10;
					originalPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
					anim = DASH;
				}
				dashTimer.reset();
			}
		}
		// Stay on top of platforms (if Ushiko is going down through the current ground level,
		// apply some linear force upwards). This method allows us to jump through the platforms from below.
		int ushikoLevel = siika->transfCrds()->deviceToUser(go->getComponent<misc::TransformComponent>()->getPosition()).y;
		if (ushikoLevel > groundLevel - 250 && ushikoLevel < groundLevel && go->getComponent<misc::PhysicsComponent>()->_body->GetLinearVelocity().y < -1)
		{
			ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 5), false);

			doubleJump = false;
			canJump = true;
			
			if (anim == JUMP_MIDDLE)
				anim = JUMP_END;
			else anim = RUN;
		}
	}
	animate();
}

void Ushiko::animate()
{
	// TODO(Jere): Step() the animation based on the animState
	go->getComponent<misc::SpriteComponent>()->getSprite()->step(9, 9, false);

	/*
	if (animTimer.getElapsedTime(SECONDS) > 0.5)
	{
		animTimer.reset();
	}
	//*/
}