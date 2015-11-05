#include "GameUI.hpp"

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
}

void GameUI::deInit()
{
	delete lt;
}

void GameUI::update(core::Siika2D *siika)
{
	lt->update();
}