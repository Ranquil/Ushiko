#include "Ushiko.hpp"

Ushiko ushiko;

Ushiko::Ushiko()
{
	// Set up all the animations (sheet, starting frame, frame amount, loop)

	animations[IDLE]        = { 1, 9, 1, false };
	animations[RUN]         = { 2, 0, 8, true  };
	animations[DASH]        = { 1, 4, 5, false };
	animations[JUMP_START]  = { 1, 0, 2, false };
	animations[JUMP_MIDDLE] = { 1, 2, 1, false };
	animations[JUMP_END]    = { 1, 3, 1, false };
	animations[DOUBLE_JUMP] = { 2, 8, 7, false };
}

Ushiko::~Ushiko()
{

}

void Ushiko::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

	misc::SpriteComponent *sheet = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		siika->_textureManager->createTexture("sprite_ushiko_1.png"),
		glm::vec2(0, 0),
		glm::vec2(0.25, 0.25))));

	misc::PhysicsComponent *physComp = new misc::PhysicsComponent;
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	physComp->setGravityScale(2);
	sheet->setZ(10);

	go->addComponent(trnsComp);
	go->addComponent(sheet);
	go->addComponent(physComp);

	go->move(glm::vec2(-1000, 0));

	prevChange = 0;
	currentAnimation = IDLE;
	currentFrame = animations[IDLE].startPos;
	animTimer.start();

	airTimer.start();
	airTimer.pause();

	health = healthMax;
	pointsAmount = 0;

	jumpTimer.start();
	doubleJump = true;
	canJump = false;

	dashTimer.start();
	dashing = false;
	xOffset = 0;
}

void Ushiko::changeSheet(core::Siika2D *siika, unsigned int sheetNum)
{
	if (sheetNum != prevChange)
	{
		go->removeComponent<misc::SpriteComponent>();
		glm::vec2 location = go->getComponent<misc::TransformComponent>()->getPosition();

		misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			location,
			glm::vec2(128, 128),
			glm::vec2(64, 64),
			sheetNum == 1 ? siika->_textureManager->createTexture("sprite_ushiko_1.png") : siika->_textureManager->createTexture("sprite_ushiko_2.png"),
			glm::vec2(0, 0),
			glm::vec2(0.25, 0.25))));
		sprtComp->setZ(10);

		go->addComponent(sprtComp);
		prevChange = sheetNum;
	}
}

void Ushiko::update(core::Siika2D *siika)
{
	if (health > healthMax)
		health = healthMax;

	glm::vec2 touchPos = glm::vec2(0, 0);
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
		touchPos = siika->transfCrds()->deviceToUser(siika->_input->touchPosition(i)._positionStart);

	// Get the current animation
	animState previousAnimation = currentAnimation;

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
					dashing = false;
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
			int ushikoPos = go->getComponent<misc::TransformComponent>()->getPosition().y;

			// Jump (tap on the left side of the screen)
			if (jumpTimer.getElapsedTime(SECONDS) > 0.2 && touchPos.x > 10 &&
				touchPos.x < siika->_graphicsContext->getDisplaySize().x / 2)
			{
				ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
				ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 48), false);

				jumpTimer.reset();

				if (canJump)
				{
					canJump = false;
					currentAnimation = JUMP_START;
					airTimer.reset();
				}
				else if (!doubleJump && airTimer.getElapsedTime(MILLISECONDS) > 300)
				{
					doubleJump = true;
					currentAnimation = DOUBLE_JUMP;
					airTimer.pause();
				}
			}
			// Dash (tap on the right side of the screen)
			else if (xOffset <= 0 && dashTimer.getElapsedTime(SECONDS) > 0.8f &&
				touchPos.x > siika->_graphicsContext->getDisplaySize().x / 2)
			{
				if (xOffset <= 0)
				{
					currentAnimation = DASH;
					dashing = true;
					xOffset = 10;
					originalPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
				}
				dashTimer.reset();
			}
		}
		// Stay on top of platforms (if Ushiko is going down through the current ground level,
		// apply some linear force upwards). This method allows us to jump through the platforms from below.
		int ushikoLevel = siika->transfCrds()->deviceToUser(go->getComponent<misc::TransformComponent>()->getPosition()).y;
		if (ushikoLevel > groundLevel - 260 && ushikoLevel < groundLevel - 200 && go->getComponent<misc::PhysicsComponent>()->_body->GetLinearVelocity().y < -1)
		{
			ushiko.go->getComponent<misc::PhysicsComponent>()->_body->SetLinearVelocity(b2Vec2(0, 0));
			ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(0, 10), false);

			if (currentAnimation == JUMP_MIDDLE)
				currentAnimation = JUMP_END;
			else if (currentAnimation != RUN)
				currentAnimation = RUN;

			doubleJump = false;
			canJump = true;
		}
	}

	if (animTimer.getElapsedTime(MILLISECONDS) > 100)
	{
		animTimer.reset();

		// Get the current animation
		animation anim = animations[currentAnimation];
		bool updateFrame = false;

		// If the new animation is in a different sheet, change to it
		changeSheet(siika, anim.sheet);

		// Check if the animation has changed
		if (currentAnimation != previousAnimation)
		{
			// Set the new animation frame
			currentFrame = anim.startPos;
			updateFrame = true;
		}
		else // Update the current animation
		{
			currentFrame += 1;

			// Check if the frame goes above the frame amount of the animation
			if (currentFrame > anim.startPos + anim.frames - 1)
			{
				// If it's a looping animation, go back to the start
				if (anim.loop)
				{
					currentFrame = anim.startPos;
					updateFrame = true;
				}
				// Transition from dash to run
				else if (currentAnimation == DASH)
				{
					currentAnimation = RUN;
					currentFrame = animations[RUN].startPos;
					changeSheet(siika, animations[RUN].sheet);
					updateFrame = true;
				}
				// Transition from start of a jump / double jump to the middle
				else if (currentAnimation == JUMP_START || currentAnimation == DOUBLE_JUMP)
				{
					currentAnimation = JUMP_MIDDLE;
					currentFrame = animations[JUMP_MIDDLE].startPos;
					changeSheet(siika, animations[JUMP_MIDDLE].sheet);
					updateFrame = true;
				}
				// Transition from the middle of a jump to the end of it
				else if (currentAnimation == JUMP_END)
				{
					currentAnimation = RUN;
					currentFrame = animations[RUN].startPos;
					changeSheet(siika, animations[RUN].sheet);
					updateFrame = true;
				}
				// Stay on the last frame
				else currentFrame -= 1;
			}
			else updateFrame = true;
		}

		// If the animation needs updating, update it
		if (updateFrame)
			go->getComponent<misc::SpriteComponent>()->getSprite()->step(currentFrame, currentFrame);
	}
}