#include "Level.hpp"
#include "Ushiko.hpp"

#include "PlainsGenerator.hpp"
#include "ForestGenerator.hpp"
#include "CastleGenerator.hpp"

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
	if (levelName == "plains")
		lg = new PlainsGenerator(siika, "plains");
	else if (levelName == "forest")
		lg = new ForestGenerator(siika, "forest");
	else lg = new CastleGenerator(siika, "castle");

	gameUI = new GameUI;
	gameUI->init(siika);

	std::string bgTexture = "background_forest_plains.png";
	if (levelName == "castle")
		bgTexture = "background_menu_castle.png";

	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();

	glm::vec2 bgPos = glm::vec2(0, 0);
	if (levelName == "castle" || levelName == "plains")
		bgPos = glm::vec2(0, -scrSize.y);

	ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(5, 0));

	bg = siika->_spriteManager->createSprite(
		bgPos,
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture(bgTexture),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setZ(100);

	theme = siika->_audioManager->createAudio("castle_theme.ogg");
	theme->setLooping(true);
	theme->play();

	cl = new colListener;
	siika->_boxWorld->SetContactListener(cl);

	paused = false;
}

void Level::deInit()
{
	theme->stop();
	//delete theme;

	bg->setPosition(glm::vec2(-3000, 0));

	delete gameUI;
	delete lg;
	delete cl;
}

int Level::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	int state = gameUI->update(siika);
	if (state == PAUSE)
		pause();
	else if (state == RESUME)
		resume();

	if (!paused)
	{
		siika->_boxWorld->Step(1.5f / 60.0f, 6, 2);

		lg->update(siika);
		ushiko.update(siika);
	}

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	if (ushiko.health <= 0)
		return MAIN_MENU;

	if (levelName == "plains")
		return PLAINS_LEVEL;
	else if (levelName == "forest")
		return FOREST_LEVEL;
	else return CASTLE_LEVEL;
}

void Level::pause()
{
	gameUI->lt->levelTimer.pause();
	theme->pause();
	paused = true;
}

void Level::resume()
{
	gameUI->lt->levelTimer.resume();
	theme->play();
	paused = false;
}