#include "EndScreen.hpp"

EndScreen::EndScreen()
{

}
EndScreen::~EndScreen()
{
	deInit();
}

void EndScreen::deInit()
{
	endScreen->setPosition(glm::vec2(-5000, 0));
}

void EndScreen::init(core::Siika2D *siika)
{
	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	
	endScreen = siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("title_screen_11_12.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	endScreen->setZ(100);
}

int EndScreen::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	siika->_spriteManager->drawSprites();
	siika->_graphicsContext->swap();

	if (siika->_input->touchPositionsActive() > 0)
		return LEVEL_SELECT;
	return END_SCREEN;
}