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
	int boxSizex = screenSize.x / 4;
	int boxSizey = screenSize.y / 4; 

	plainsLevel = new misc::GameObject;
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

	forestLevel = new misc::GameObject;

	 lvlSelectTexture = siika->_textureManager->createTexture("tile_castle_middle.png");
	 sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(boxSizex, boxSizey),
		glm::vec2(0, 0),
		lvlSelectTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	 transComp = new misc::TransformComponent;

	forestLevel->addComponent(sprtComp);
	forestLevel->addComponent(transComp);

	castleLevel = new misc::GameObject;

	lvlSelectTexture = siika->_textureManager->createTexture("background_castle.png");
	sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(boxSizex, boxSizey),
		glm::vec2(0, 0),
		lvlSelectTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	 transComp = new misc::TransformComponent;

	castleLevel->addComponent(sprtComp);
	castleLevel->addComponent(transComp);

	plainsLevel->move(glm::vec2(screenSize.x - screenSize.x * 0.9f, screenSize.y - screenSize.y * 1.5f ));
	forestLevel->move(glm::vec2(screenSize.x / 1.5f, screenSize.y - screenSize.y * 1.5f));
	castleLevel->move(glm::vec2(screenSize.x * 1.2f, screenSize.y - screenSize.y * 1.5f));
}

void LevelSelect::deInit(core::Siika2D *siika)
{
	delete plainsLevel, forestLevel, castleLevel;
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