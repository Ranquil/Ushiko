#include "Level.hpp"
#include "Ushiko.hpp"
#include "Sound.hpp"

Level::Level(std::string name)
{
	levelName = name;
}

Level::~Level()
{
	deInit();
}

void Level::init(core::Siika2D *siika)
{
	/* ----- Initialize the boss ----- */

	if (levelName == "boss")
	{
		boss = new Boss();
		boss->init(siika);
	}
	else boss = nullptr;

	/* ----- Initialize GameUI ----- */

	gameUI = new GameUI;
	if (levelName == "boss")
		gameUI->init(siika, levelName, boss);
	else gameUI->init(siika, levelName);

	/* ----- Initialize the background texture & position ----- */

	std::string bgTexture = "background_forest_plains.png";
	if (levelName == "castle" || levelName == "boss")
		bgTexture = "background_menu_castle.png";

	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();

	glm::vec2 bgPos = glm::vec2(0, 0);
	if (levelName == "castle" || levelName == "plains" || levelName == "boss")
		bgPos = glm::vec2(0, -scrSize.y);

	bg = siika->_spriteManager->createSprite(
		bgPos,
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture(bgTexture),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setZ(100);

	/* ----- And other stuff ----- */

	lg = new LevelGenerator(siika, levelName);
	ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(5, 0));

	unlocked = false;
	paused = false;
	genTimer.start();

	unlock = siika->_spriteManager->createSprite(
		glm::vec2(-5000, 0),
		glm::vec2(512, 512),
		glm::vec2(256, 256),
		siika->_textureManager->createTexture("tile_unlock.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	unlock->setZ(0);
	unlockTimes = 0;

	if (levelName == "castle")
		sound.playSound(CASTLE_THEME);
	else if (levelName == "boss")
		sound.playSound(BOSS_THEME);
}

void Level::deInit()
{
	if (levelName == "castle")
		sound.stopSound(CASTLE_THEME);
	else if (levelName == "boss")
		sound.stopSound(BOSS_THEME);

	bg->setPosition(glm::vec2(-5000, 0));
	unlock->setPosition(glm::vec2(-5000, 0));

	delete gameUI;
	delete lg;

	if (boss != nullptr)
		delete boss;
}

int Level::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	int state;
	if (levelName == "boss")
		state = gameUI->update(siika, boss);
	else state = gameUI->update(siika);

	if (state == PAUSE)
		pause();
	else if (state == RESUME)
		resume();

	if (!paused && genTimer.getElapsedTime(MILLISECONDS) > 10)
	{
		genTimer.reset();
		siika->_boxWorld->Step(1.5f / 60.0f, 6, 2);

		int coins = ushiko.coinCount;
		if (unlockTimes > 0)
		{
			unlockTimes -= 1;
			if (unlockTimes <= 0)
				unlock->setPosition(glm::vec2(-5000, 0));
		}

		lg->update(siika);
		ushiko.update(siika);

		if (coins == ushiko.coinCount - 1)
			sound.playSound(COIN);

		if (boss != nullptr)
			boss->update(siika);

		int pointsNeeded = 500;
		if (levelName == "forest")
			pointsNeeded = 1000;
		else if (levelName != "plains")
			pointsNeeded = 2000;

		if (!unlocked && ushiko.pointsAmount >= pointsNeeded)
		{
			unlocked = true;
			misc::File *file = siika->getFile("progress.txt");
			std::string read = file->readFile();

			glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();

			int levels = 0;
			if (read.find("1") != std::string::npos) levels += 1;
			if (read.find("2") != std::string::npos) levels += 1;
			if (read.find("3") != std::string::npos) levels += 1;

			if (levelName == "plains" && levels == 0)
			{
				file->writeFile("1");
				unlock->setPosition(glm::vec2(scrSize.x / 2, scrSize.y / 2));
				unlockTimes = 100;
				sound.playSound(LEVEL_UNLOCK);
				ushiko.pointsAmount = 0;
			}
			if (levelName == "forest" && levels == 1)
			{
				file->writeFile("12");
				unlock->setPosition(glm::vec2(scrSize.x / 2, scrSize.y / 2));
				unlockTimes = 100;
				sound.playSound(LEVEL_UNLOCK);
				ushiko.pointsAmount = 0;
			}
			if (levelName == "castle" && levels == 2)
			{
				file->writeFile("123");
				unlock->setPosition(glm::vec2(scrSize.x / 2, scrSize.y / 2));
				unlockTimes = 100;
				sound.playSound(LEVEL_UNLOCK);
				ushiko.pointsAmount = 0;
			}
		}
	}

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	if (boss != nullptr && boss->bossHealth <= 0)
	{
		delete ushiko.go;
		return GAME_OVER;
	}
	if (ushiko.health <= 0)
	{
		delete ushiko.go;
		return GAME_OVER;
	}

	if (levelName == "plains")
		return PLAINS_LEVEL;
	else if (levelName == "forest")
		return FOREST_LEVEL;
	else if (levelName == "castle")
		return CASTLE_LEVEL;
	else return BOSS_LEVEL;
}

void Level::pause()
{
	genTimer.pause();
	paused = true;
}

void Level::resume()
{
	genTimer.reset();
	paused = false;
}