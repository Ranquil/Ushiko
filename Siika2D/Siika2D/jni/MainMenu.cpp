#include "MainMenu.hpp"

MainMenu::MainMenu(core::Siika2D *siika)
{
	graphics::Texture *startGameTexture = siika->_textureManager->createTexture("temp_Menu_Button");

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
}

MainMenu::~MainMenu()
{

}


int MainMenu::update(core::Siika2D *siika)
{
	return MAIN_MENU;
}