#include "LevelSelect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

LevelSelect::LevelSelect()
{

}

LevelSelect::~LevelSelect()
{
	deInit();
}

void LevelSelect::init(core::Siika2D *siika)
{
	misc::File *file = siika->getFile("progress.txt");
	std::string read = file->readFile();

	unlocked = 0;
	if (read.find("1") != std::string::npos) unlocked = 1;
	if (read.find("2") != std::string::npos) unlocked = 2;
	if (read.find("3") != std::string::npos) unlocked = 3;

	unlocked = 3;

	glm::vec2 screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());
	boxSizex = siika->_graphicsContext->getDisplaySize().x / 4;
	boxSizey = siika->_graphicsContext->getDisplaySize().y / 4;

	plainsLevel = new misc::GameObject;
	castleLevel = new misc::GameObject;
	forestLevel = new misc::GameObject;
	bossLevel = new misc::GameObject;

	for (int i = 0; i < 4; i++)
	{
		graphics::Texture *lvlSelectTexture;
		
		switch (i)
		{
			case 0:	lvlSelectTexture = siika->_textureManager->createTexture("background_plains.png"); break;
			case 1:	
				if(unlocked >= 1)
					lvlSelectTexture = siika->_textureManager->createTexture("background_forest.png");
				else lvlSelectTexture = siika->_textureManager->createTexture("tile_castle_middle.png");
				break;
			case 2:
				if (unlocked >= 2)
					lvlSelectTexture = siika->_textureManager->createTexture("background_castle.png");
				else lvlSelectTexture = siika->_textureManager->createTexture("tile_castle_middle.png");
				break;
			case 3:
				if (unlocked >= 3)
					lvlSelectTexture = siika->_textureManager->createTexture("background_castle.png");
				else lvlSelectTexture = siika->_textureManager->createTexture("tile_castle_middle.png");
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
			case 0:	plainsLevel->addComponent(sprtComp); plainsLevel->addComponent(transComp); break;
			case 1:	forestLevel->addComponent(sprtComp); forestLevel->addComponent(transComp); break;
			case 2:	castleLevel->addComponent(sprtComp); castleLevel->addComponent(transComp); break;
			case 3: bossLevel->addComponent(sprtComp); bossLevel->addComponent(transComp); break;
			default: break;
		}
	}

	float test = screenSize.x / 23;

	plainsLevel->move(glm::vec2(test, -screenSize.y / 5));
	forestLevel->move(glm::vec2(screenSize.x / 3 + test, -screenSize.y / 5));
	castleLevel->move(glm::vec2(screenSize.x / 1.5 + test, -screenSize.y / 5));
	bossLevel->move(glm::vec2(screenSize.x / 3 + test, -screenSize.y / 2));

	siika->_graphicsContext->setClearColor(graphics::Color(0, 255, 255, 255));
}

void LevelSelect::deInit()
{
	delete plainsLevel;
	delete forestLevel; 
	delete castleLevel;
	delete bossLevel;
}

bool LevelSelect::isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + boxSizex) && 
		touchPosition.y > box.y && touchPosition.y < box.y + boxSizey)
		return true;
	return false;
}

int LevelSelect::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	touchPosition = glm::vec2(0, 0);
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
		touchPosition = siika->_input->touchPosition(i)._positionStart;

	if (siika->_input->touchPositionsActive() > 0)
	{
		if (isIntersecting(touchPosition, plainsLevel->getComponent<misc::TransformComponent>()->getPosition()))
			return PLAINS_LEVEL;
		else if (unlocked >= 1 && isIntersecting(touchPosition, forestLevel->getComponent<misc::TransformComponent>()->getPosition()))
			return FOREST_LEVEL;
		else if (unlocked >= 2 && isIntersecting(touchPosition, castleLevel->getComponent<misc::TransformComponent>()->getPosition()))
			return CASTLE_LEVEL;
		else if (unlocked >= 3 && isIntersecting(touchPosition, bossLevel->getComponent<misc::TransformComponent>()->getPosition()))
			return BOSS_LEVEL;
	}

	plainsLevel->update();
	forestLevel->update();
	castleLevel->update();
	bossLevel->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();
	 
	return LEVEL_SELECT;
}