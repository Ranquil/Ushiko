#include "Puff.hpp"

Puff::Puff()
{

}

Puff::~Puff()
{
	if (go != NULL)
		delete go;
}

void Puff::init(core::Siika2D *siika, int x, int y)
{
	go = new misc::GameObject;
	graphics::Texture *puffTexture;

	puffTexture = siika->_textureManager->createTexture("fx_enemydeath.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(x, y),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		puffTexture,
		glm::vec2(0, 0),
		glm::vec2(0.25, 0.25))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(5);

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);
	go->move(glm::vec2(x, y));

	animTimer.start();
	animSteps = 0;
}

void Puff::update(core::Siika2D *siika)
{
	go->update();
	if (animTimer.getElapsedTime(MILLISECONDS) > 100)
	{
		animTimer.reset();
		go->getComponent<misc::SpriteComponent>()->getSprite()->step();

		animSteps += 1;
		if (animSteps > 6)
		{
			delete go;
			go = NULL;
		}
	}
}