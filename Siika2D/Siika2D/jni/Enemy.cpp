#include "Enemy.hpp"

Enemy::Enemy(std::string enemyTextureName)
{
	this->enemyTextureName = enemyTextureName;
}

Enemy::~Enemy()
{
	deInit();
}

void Enemy::init(core::Siika2D *siika, int firstFrame, int lastFrame)
{
	go = new misc::GameObject;

	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;

	graphics::Texture *enemyTexture = siika->_textureManager->createTexture(enemyTextureName);

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(256, 256),
		glm::vec2(128, 128),
		enemyTexture,
		glm::vec2(0, 0),
		(lastFrame != 0 ? glm::vec2(0.2, 0.2) : glm::vec2(0.5, 0.5)))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(20);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	animationTimer.start();
}

void Enemy::deInit()
{
	delete go;
}

void Enemy::update(core::Siika2D *siika)
{
	if (animationTimer.getElapsedTime(MILLISECONDS) >= 10)
	{
		if (lastFrame > 0)
			go->getComponent<misc::SpriteComponent>()->getSprite()->step(firstFrame, lastFrame, true);
		else go->getComponent<misc::SpriteComponent>()->getSprite()->step();

		animationTimer.reset();
	}
	go->update();
}