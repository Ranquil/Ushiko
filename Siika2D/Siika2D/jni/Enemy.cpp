#include "Enemy.hpp"

Enemy::Enemy(std::string enemyTextureName)
{
	this->enemyTextureName = enemyTextureName;
}

Enemy::~Enemy()
{
	deInit();
}

void Enemy::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

	graphics::Texture *enemyTexture = siika->_textureManager->createTexture(enemyTextureName);

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(256, 256),
		glm::vec2(128, 128),
		enemyTexture,
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5))));

	go->addComponent(sprtComp);

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
		go->getComponent<misc::SpriteComponent>()->getSprite()->step();
		animationTimer.reset();
	}
	go->update();
}