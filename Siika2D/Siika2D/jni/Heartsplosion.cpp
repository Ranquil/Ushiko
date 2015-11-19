#include "Heartsplosion.hpp"

Heartsplosion::Heartsplosion()
{

}

Heartsplosion::~Heartsplosion()
{
	if (go != NULL)
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
}

void Heartsplosion::update(core::Siika2D *siika)
{
	glm::vec2 screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());
	if (xPos < 0 || xPos > screenSize.x ||
		-yPos < 0 || -yPos > screenSize.y)
	{
		delete go;
		go = NULL;
		return;
	}
	go->update();
	go->move(glm::vec2(xPos += force.x, yPos += force.y));
}