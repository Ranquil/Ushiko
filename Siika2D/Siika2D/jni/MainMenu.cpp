#include "MainMenu.hpp"

MainMenu::MainMenu()
{
	hasBeenInit = false;
}

MainMenu::~MainMenu()
{
	deInit();
}

void MainMenu::init(core::Siika2D *siika)
{
	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	bg = siika->_spriteManager->createSprite(
		glm::vec2(-5000, 0),
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("background_menu_castle.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setZ(100);

	if (!hasBeenInit)
	{
		logo = siika->_spriteManager->createSprite(
			glm::vec2(scrSize.x / 2, scrSize.y / 2),
			glm::vec2(512, 512),
			glm::vec2(256, 256),
			siika->_textureManager->createTexture("logo.png"),
			glm::vec2(0, 0),
			glm::vec2(1, 1));
		logo->setZ(110);
	}
	else bg->setPosition(glm::vec2(0, 0));

	siika->_graphicsContext->setClearColor(graphics::Color(0, 0, 0, 0));
	initTimer.start();
}

void MainMenu::deInit()
{
	bg->setPosition(glm::vec2(-5000, 0));
	logo->setPosition(glm::vec2(-5000, 0));
}

bool MainMenu::isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + 256) &&
		touchPosition.y > box.y && touchPosition.y < box.y + 256)
		return true;
	return false;
}

int MainMenu::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	if (!hasBeenInit)
	{
		if (initTimer.getElapsedTime(SECONDS) > 3)
		{
			hasBeenInit = true;
			bg->setPosition(glm::vec2(0, 0));
			logo->setPosition(glm::vec2(-5000, 0));
		}
	}
	if (siika->_input->touchPositionsActive() > 0)
		return LEVEL_SELECT;

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return MAIN_MENU;
}