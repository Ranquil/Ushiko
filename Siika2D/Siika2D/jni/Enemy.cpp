#include "Enemy.hpp"
#include "Ushiko.hpp"

Enemy::Enemy(std::string enemyTextureName, bool fourByfour)
{
	this->enemyTextureName = enemyTextureName;
	this->flies = false;
	this->rising = false;
	this->fbf = fourByfour;
}

Enemy::~Enemy()
{
	deInit();
}

void Enemy::init(core::Siika2D *siika, int firstFrame, int lastFrame, int animeSpeed)
{
	go = new misc::GameObject;

	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	this->animeSpeed = animeSpeed;

	graphics::Texture *enemyTexture = siika->_textureManager->createTexture(enemyTextureName);

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		enemyTexture,
		glm::vec2(0, 0),
		fbf ? glm::vec2(0.25, 0.25) : (lastFrame != 0 ? glm::vec2(0.2, 0.2) : glm::vec2(0.5, 0.5)))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(30);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	animationTimer.start();
	hasHit = false;
}

void Enemy::deInit()
{
	delete go;
}

void Enemy::update(core::Siika2D *siika)
{
	go->update();

	if (animationTimer.getElapsedTime(MILLISECONDS) >= animeSpeed)
	{
		if (lastFrame != 0)
			go->getComponent<misc::SpriteComponent>()->getSprite()->step(firstFrame, lastFrame, true);
		else go->getComponent<misc::SpriteComponent>()->getSprite()->step();

		animationTimer.reset();
	}
}