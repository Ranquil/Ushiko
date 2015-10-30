#include "LevelSelect.hpp"


LevelSelect::LevelSelect()
{

}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::init(core::Siika2D *siika)
{
	plainsLevel = new misc::GameObject;
	glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
	int boxSizex = screenSize.x / 4;
	int boxSizey = screenSize.y / 4; 

	graphics::Texture *lvlSelectTexture = siika->_textureManager->createTexture("background_plains.png");
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0,0),
		glm::vec2(boxSizex, boxSizey),
		glm::vec2(0, 0),
		lvlSelectTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;

	plainsLevel->addComponent(sprtComp);
	plainsLevel->addComponent(transComp);

	plainsLevel->move(glm::vec2(screenSize.x / 2, screenSize.y / 2));




}

void LevelSelect::deInit(core::Siika2D *siika)
{
	delete plainsLevel;
}


int LevelSelect::update(core::Siika2D *siika)
{

	siika->_graphicsContext->clear();

	plainsLevel->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return LEVEL_SELECT;
}