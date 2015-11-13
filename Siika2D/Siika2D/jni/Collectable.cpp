#include "Collectable.hpp"
#include "Ushiko.hpp"

Collectable::Collectable()
{

}

Collectable::~Collectable()
{
	deinit();
}


void Collectable::init(core::Siika2D *siika)
{
	go = new misc::GameObject;

	graphics::Texture *collectableTexture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		collectableTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(20);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);
}

void Collectable::deinit()
{
	delete go;
}