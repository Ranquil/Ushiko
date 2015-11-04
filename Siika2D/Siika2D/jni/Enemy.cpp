#include "Enemy.hpp"

Enemy::Enemy(std::string enemyTextureName)
{
	this->enemyTextureName = enemyTextureName;
}

Enemy::~Enemy()
{

}

void Enemy::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

	graphics::Texture *enemyTexture = siika->_textureManager->createTexture(enemyTextureName);

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		enemyTexture,
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5))));

	go->addComponent(sprtComp);

	
}

void Enemy::deInit(core::Siika2D *siika)
{
	delete go;
}


void Enemy::update(core::Siika2D *siika)
{
	go->getComponent<misc::SpriteComponent>()->getSprite()->step();
	go->update();
}