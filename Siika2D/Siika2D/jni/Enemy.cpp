#include "Enemy.hpp"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

	graphics::Texture *enemyTexture = siika->_textureManager->createTexture("sprite_shimapanda");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		enemyTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	go->addComponent(sprtComp);

	
}


void Enemy::update(core::Siika2D *siika, colListener *collisions)
{

	go->update();
}