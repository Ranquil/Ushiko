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
	castleLevel = new misc::GameObject;
	forestLevel = new misc::GameObject;

	for (int i = 0; i < 3; i++)
	{
		graphics::Texture *lvlSelectTexture;
		switch (i)
		{
			case 0:	lvlSelectTexture = siika->_textureManager->createTexture("background_plains.png");	break;
			case 1:	lvlSelectTexture = siika->_textureManager->createTexture("tile_castle_middle.png");	break;
			case 2:	lvlSelectTexture = siika->_textureManager->createTexture("background_castle.png");	break;
			default: break;
		}

		misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			glm::vec2(0, 0),
			glm::vec2(boxSizex, boxSizey),
			glm::vec2(0, 0),
			lvlSelectTexture,
			glm::vec2(0, 0),
			glm::vec2(1, 1))));
		misc::TransformComponent *transComp = new misc::TransformComponent;

		switch (i)
		{
			case 0:	plainsLevel->addComponent(sprtComp); plainsLevel->addComponent(transComp);	break;
			case 1:	forestLevel->addComponent(sprtComp); forestLevel->addComponent(transComp);	break;
			case 2:	castleLevel->addComponent(sprtComp); castleLevel->addComponent(transComp);	break;
			default: break;
		}
	}


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
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		touchPosition = siika->_input->touchPosition(i)._positionCurrent + siika->_camera->getPosition();
	}

	/*if (touchPosition == plainsLevel->getComponent<misc::TransformComponent>()->getPosition());
	{
		return CASTLE_LEVEL;
	}*/

	plainsLevel->update();
	forestLevel->update();
	castleLevel->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return LEVEL_SELECT;
}