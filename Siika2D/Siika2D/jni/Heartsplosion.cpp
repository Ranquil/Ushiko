#include "Heartsplosion.hpp"

Heartsplosion::Heartsplosion()
{

}

Heartsplosion::~Heartsplosion()
{
	delete go;
}

void Heartsplosion::init(core::Siika2D *siika, int x, int y)
{
	go = new misc::GameObject;
	graphics::Texture *heartTexture;

	heartTexture = siika->_textureManager->createTexture("ui_heart_full.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(32, 32),
		glm::vec2(16, 16),
		heartTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(5);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	force = glm::vec2(mrand48() % 9 + 1, lrand48() % 9 + 1);

//	lifeTime = drand48() + 0.4f;
//	lifeTimer.start();
}

void Heartsplosion::update()
{
	go->update();
	go->move(glm::vec2(xPos += force.x, yPos += force.y));
}