#include "MainMenu.hpp"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{
	deInit();
}

void MainMenu::init(core::Siika2D *siika)
{

	graphics::Texture *startGameTexture = siika->_textureManager->createTexture("Temp_Menu_button.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(256, 256),
		glm::vec2(128, 128),
		startGameTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	misc::TransformComponent *transComp = new misc::TransformComponent;
	transComp->setPosition(glm::vec2(0, 0));

	startGameButton->addComponent(sprtComp);
	startGameButton->addComponent(transComp);

	glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
	startGameButton->move(glm::vec2(screenSize.x / 1.5f, screenSize.y - screenSize.y * 1.5));

	siika->_graphicsContext->setClearColor(graphics::Color(255, 0, 255, 255));
}

void MainMenu::deInit()
{
	
}

bool MainMenu::isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + 256) &&
		touchPosition.y > box.y && touchPosition.y < box.y + 256)
	{
		return true;
	}
	return false;
}

int MainMenu::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();
	//for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	//{
	//	touchPosition = siika->_input->touchPosition(i)._positionCurrent;
	//}
	//if (isIntersecting(touchPosition, startGameButton->getComponent<misc::TransformComponent>()->getPosition()))
	//{
	//	return LEVEL_SELECT;
	//}

	startGameButton->update();

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return MAIN_MENU;
}