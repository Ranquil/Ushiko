#include "LevelSelect.hpp"


LevelSelect::LevelSelect()
{

}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::init(core::Siika2D *siika)
{
	glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
	int boxSizex = screenSize.x / 5;
	int boxSizey = screenSize.y / 5; 

	graphics::Texture *lvlSelectTexture = siika->_textureManager->createTexture("background_plains");
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(boxSizex, boxSizey),
		glm::vec2(256, 256),
		lvlSelectTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;

	plainsLevel.addComponent(sprtComp);
	plainsLevel.addComponent(transComp);




}

void LevelSelect::deInit(core::Siika2D *siika)
{

}


int LevelSelect::update(core::Siika2D *siika)
{

	siika->_graphicsContext->clear();

//	siika->_spriteManager->drawSprites();
//	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return LEVEL_SELECT;
}