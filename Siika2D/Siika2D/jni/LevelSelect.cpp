#include "LevelSelect.hpp"


LevelSelect::LevelSelect()
{

}

LevelSelect::~LevelSelect()
{

}

int LevelSelect::update(core::Siika2D *siika)
{

	siika->_graphicsContext->clear();

//	siika->_spriteManager->drawSprites();
//	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return LEVEL_SELECT;
}