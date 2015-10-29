#include "MainMenu.hpp"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Init(core::Siika2D *siika)
{
	graphics::Texture *startGameTexture = siika->_textureManager->createTexture("Temp_Menu_button.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		startGameTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	misc::TransformComponent *transComp = new misc::TransformComponent;
	transComp->setPosition(glm::vec2(0, 0));

	startGameButton.addComponent(sprtComp);
	startGameButton.addComponent(transComp);

	glm::vec2 screenSize = siika->_graphicsContext->getDisplaySize();
	startGameButton.move(glm::vec2(screenSize.x / 2, screenSize.y / 2));
}

int MainMenu::update(core::Siika2D *siika)
{
	if (!hasBeenInit)
	{
		Init(siika);
	}

	return MAIN_MENU;
}