#include "LevelSelect.hpp"
#include "Sound.hpp"

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

	std::string bgTexture = "background_instructions.png";
	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	glm::vec2 bgPos = glm::vec2(0, -scrSize.y);

	bg = siika->_spriteManager->createSprite(
		bgPos,
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture(bgTexture),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setZ(100);

	question = siika->_spriteManager->createSprite(
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(128, 128),
		glm::vec2(160, 160),
		siika->_textureManager->createTexture("tile_question.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	question->setZ(80);

	forNextLevel = siika->_spriteManager->createSprite(
		glm::vec2(scrSize.x / 2, scrSize.y + scrSize.y / 3),
		glm::vec2(512, 512),
		glm::vec2(256, 512),
		siika->_textureManager->createTexture("tile_level_sheet.png"),
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5));
	forNextLevel->setZ(70);

	for (int i = 0; i < unlocked; i++)
	{
		forNextLevel->step();
	}

	instructions = false;
	inputTimer.start();

	for (int i = 0; i < 4; i++)
	{
		misc::GameObject *go = new misc::GameObject;
		graphics::Texture *lockTexture = siika->_textureManager->createTexture("tile_lock.png");

		misc::SpriteComponent *sprtCompLock = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			glm::vec2(-1000, 0),
			glm::vec2(64, 64),
			glm::vec2(0, 0),
			lockTexture,
			glm::vec2(0, 0),
			glm::vec2(1, 1))));
		sprtCompLock->setZ(80);
		misc::TransformComponent *transCompLock = new misc::TransformComponent;

		go->addComponent(sprtCompLock);
		go->addComponent(transCompLock);

		levelLocks.push_back(go);
		graphics::Texture *lvlSelectTexture;
		
		switch (i)
		{
			case 0:	lvlSelectTexture = siika->_textureManager->createTexture("background_plains.png"); break;
			case 1:	lvlSelectTexture = siika->_textureManager->createTexture("background_forest.png"); break;
			case 2: lvlSelectTexture = siika->_textureManager->createTexture("background_castle.png"); break;
			case 3: lvlSelectTexture = siika->_textureManager->createTexture("background_boss.png"); break;
			default: break;
		}

		misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			glm::vec2(0, 0),
			glm::vec2(boxSizex, boxSizey),
			glm::vec2(0, 0),
			lvlSelectTexture,
			glm::vec2(0, 0),
			glm::vec2(1, 1))));
		sprtComp->setZ(90);
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

	for (int j = unlocked; j < 4; j++)
	{
		switch (j)
		{
			case 0: levelLocks[0]->move(glm::vec2(screenSize.x / 3 + screenSize.x / 23, -screenSize.y / 5)); break;
			case 1: levelLocks[1]->move(glm::vec2(screenSize.x / 1.5 + screenSize.x / 23, -screenSize.y / 5)); break;
			case 2: levelLocks[2]->move(glm::vec2(screenSize.x / 3 + screenSize.x / 23, -screenSize.y / 2)); break;
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
	bg->setPosition(glm::vec2(-5000, 0));
	question->setPosition(glm::vec2(-5000, 0));

	delete plainsLevel;
	delete forestLevel; 
	delete castleLevel;
	delete bossLevel;

	for (misc::GameObject* go : levelLocks)
		delete go;
	levelLocks.clear();
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
		glm::vec2 insBox = siika->_graphicsContext->getDisplaySize();
		if (isIntersecting(touchPosition, plainsLevel->getComponent<misc::TransformComponent>()->getPosition()))
		{
			sound.playSound(SELECT);
			return PLAINS_LEVEL;
		}
		else if (unlocked >= 1 && isIntersecting(touchPosition, forestLevel->getComponent<misc::TransformComponent>()->getPosition()))
		{
			sound.playSound(SELECT);
			return FOREST_LEVEL;
		}
		else if (unlocked >= 2 && isIntersecting(touchPosition, castleLevel->getComponent<misc::TransformComponent>()->getPosition()))
		{
			sound.playSound(SELECT);
			return CASTLE_LEVEL;
		}
		else if (unlocked >= 3 && isIntersecting(touchPosition, bossLevel->getComponent<misc::TransformComponent>()->getPosition()))
		{
			sound.playSound(SELECT);
			return BOSS_LEVEL;
		}
		else if (!instructions && isIntersecting(touchPosition, glm::vec2(insBox.x - 128, insBox.y - 128)))
		{
			if (inputTimer.getElapsedTime(SECONDS) > 0.5)
			{
				inputTimer.reset();
				instructions = true;
				bg->setPosition(glm::vec2(0, 0));
				bg->setZ(0);
				sound.playSound(SELECT);
			}
		}
		else if (instructions)
		{
			if (inputTimer.getElapsedTime(SECONDS) > 0.5)
			{
				inputTimer.reset();
				instructions = false;
				bg->setPosition(glm::vec2(0, -siika->_graphicsContext->getDisplaySize().y));
				bg->setZ(100);
				sound.playSound(SELECT);
			}
		}
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