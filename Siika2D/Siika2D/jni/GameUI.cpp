#include "GameUI.hpp"
#include <sstream>

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

void GameUI::init(core::Siika2D *siika)
{
	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);

	gemTextUI = siika->_textManager->createText();
	gemTextUI->setFont("arial.ttf");
	gemTextUI->setPosition(-0.95, -0.95);
	gemTextUI->setFontSize(64);
}

void GameUI::deInit()
{
	delete lt;
}

void GameUI::update(core::Siika2D *siika)
{
	lt->update();

	std::ostringstream gemText;

	gemText << gemCount << " / " << maxGems;
	
	gemTextUI->setText(gemText.str());
}