
#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"

#include <Box2D/Box2D.h>

#include "LevelGenerator.hpp"
#include "LevelTimer.hpp"

core::Siika2D *siika = core::Siika2D::UI();
misc::GameObject ushiko;
glm::vec2 position;

LevelGenerator *lg;
LevelTimer *lt;

void siika_init()
{
	graphics::Texture *ushikoTexture = siika->_textureManager->createTexture("erg.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(0, 0), glm::vec2(128, 128), glm::vec2(64, 64), ushikoTexture, glm::vec2(0, 0), glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;
//	misc::PhysicsComponent *physComp = new misc::PhysicsComponent;
	transComp->setPosition(glm::vec2(0, 0));

	ushiko.addComponent(transComp);
	ushiko.addComponent(sprtComp);
//	ushiko.addComponent(physComp);

	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));

	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	lg = new LevelGenerator(siika);
}

void siika_main()
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
	}

	siika->_boxWorld->Step(1.f / 60.f, 6, 2);

	siika->_graphicsContext->clear();

	ushiko.getComponent<misc::TransformComponent>()->setPosition(position);
//	ushiko.getComponent<misc::PhysicsComponent>()->setPosition(position);

	ushiko.update();

	if (lg->generatorTimer.getElapsedTime(MILLISECONDS) > 10)
	{
		lg->generatorTimer.reset();
		lg->update(siika);
	}

	lt->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();
}
