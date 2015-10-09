
#include "..\engine\core\Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"

#include "LevelGenerator.hpp"
#include "LevelTimer.hpp"

core::Siika2D *siika = core::Siika2D::UI();
misc::GameObject ushiko;
glm::vec2 position;

LevelGenerator* lg;
LevelTimer* lt;

void siika_init()
{
	graphics::Texture *ushikoTexture = siika->_textureManager->createTexture("erg.png");

	misc::SpriteComponent* sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(0, 0), glm::vec2(128, 128), glm::vec2(64, 64), ushikoTexture, glm::vec2(0, 0), glm::vec2(1, 1))));
	misc::TransformComponent* transComp = new misc::TransformComponent();
	transComp->setPosition(glm::vec2(100, 100));

	ushiko.addComponent(transComp);
	ushiko.addComponent(sprtComp);

	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));

	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	lg = new LevelGenerator;
	lg->initSprites(siika, "tile_grass_left_corner.png", "tile_grass_middle.png", "tile_grass_right_corner.png");
}

void siika_main()
{
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
	}

	siika->_graphicsContext->clear();

	ushiko.getComponent<misc::TransformComponent>()->setPosition(position);
	ushiko.update();

	lg->update();
	lt->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();
}
