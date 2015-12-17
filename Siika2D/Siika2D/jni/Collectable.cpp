#include "Collectable.hpp"
#include "Ushiko.hpp"

Collectable::Collectable()
{

}

Collectable::~Collectable()
{
	deinit();
}

void Collectable::init(core::Siika2D *siika, bool isHeart)
{
	this->isHeart = isHeart;
	go = new misc::GameObject;
	graphics::Texture *collectableTexture;

	if (isHeart == false)
	{
		int coin = lrand48() % 6;
		switch (coin)
		{
			case 1: collectableTexture = siika->_textureManager->createTexture("sprite_coin_gold.png"); coinType = GOLD; break;
			case 2: case 3: collectableTexture = siika->_textureManager->createTexture("sprite_coin_silver.png"); coinType = SILVER; break;
			default: collectableTexture = siika->_textureManager->createTexture("sprite_coin_bronze.png"); coinType = BRONZE; break;
		}
	}
	else
		collectableTexture = siika->_textureManager->createTexture("ui_heart_full.png");
	
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		collectableTexture,
		glm::vec2(0, 0),
		isHeart ? glm::vec2(1, 1) : glm::vec2(0.5,0.5))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(20);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	animTimer.start();
}

void Collectable::update()
{
	if (animTimer.getElapsedTime(SECONDS) > 0.1f && isHeart == false)
	{
		animTimer.reset();
		go->getComponent<misc::SpriteComponent>()->getSprite()->step();
	}
}

void Collectable::deinit()
{
	delete go;
}