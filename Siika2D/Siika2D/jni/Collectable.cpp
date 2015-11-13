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
		glm::vec2(32, 32),
		glm::vec2(64, 64),
		collectableTexture,
		glm::vec2(0, 0),
		glm::vec2(0, 0))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(30);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);
}

void Collectable::deinit()
{
	delete go;
}

bool Collectable::isIntersecting(glm::vec2 thisPosition, glm::vec2 ushikoPosition)
{
	if ((ushikoPosition.x > thisPosition.x && ushikoPosition.x < thisPosition.x + 32) &&
		ushikoPosition.y > thisPosition.y && ushikoPosition.y < thisPosition.y + 32)
		return true;
	return false;
}

void Collectable::update(core::Siika2D *siika)
{
	ushikoPosition = ushiko.go->getComponent<misc::TransformComponent>()->getPosition();

	if (isIntersecting(go->getComponent<misc::TransformComponent>()->getPosition(), ushikoPosition))
	{
		ushiko.gemCount += 1;
		delete this;
	}
}