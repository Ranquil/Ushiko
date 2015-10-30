#include "MainMenu.hpp"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::init(core::Siika2D *siika)
{
	graphics::Texture *startGameTexture = siika->_textureManager->createTexture("Temp_Menu_button.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		startGameTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	misc::TransformComponent *transComp = new misc::TransformComponent;
	transComp->setPosition(glm::vec2(0, 0));

	startGameButton.addComponent(sprtComp);
	startGameButton.addComponent(transComp);

	glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
	startGameButton.move(glm::vec2(screenSize.x / 2, screenSize.y / 2));

	siika->_graphicsContext->setClearColor(graphics::Color(255, 0, 255, 255));
}

void MainMenu::deInit(core::Siika2D *siika)
{
	
}

int MainMenu::update(core::Siika2D *siika)
{
	return MAIN_MENU;
}