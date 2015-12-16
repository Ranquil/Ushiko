#include "GameOver.hpp"
#include "Ushiko.hpp"

#include <sstream>

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	deInit();
}

void GameOver::init(core::Siika2D *siika)
{
	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();

	gameOver = siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("background_gameover.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	gameOver->setZ(100);

	deadUshiko = siika->_spriteManager->createSprite(
		glm::vec2(scrSize.x / 2, scrSize.y / 2),
		glm::vec2(128, 128),
		glm::vec2(64, 64),
		siika->_textureManager->createTexture("sprite_ushiko_death.png"),
		glm::vec2(0, 0),
		glm::vec2(0.25, 0.25));
	deadUshiko->setZ(10);
	deathSteps = 0;
	deathFrames = 0;

	enemiesText = siika->_textManager->createText();
	enemiesText->setFont("coolvetica.ttf");
	enemiesText->setPosition(-0.7f, -0.5f);
	enemiesText->setFontSize(64);

	std::stringstream enm;
	enm << "Enemies killed: " << ushiko.enemiesKilled << "   Total score: " << ushiko.pointsAmount;
	enemiesText->setText(enm.str());

	/*scoreText = siika->_textManager->createText();
	scoreText->setFont("coolvetica.ttf");
	scoreText->setPosition(-0.5f, -0.2f);
	scoreText->setFontSize(64);

	std::stringstream scr;
	scr << "Total score: " << ushiko.pointsAmount;
	scoreText->setText(scr.str());*/
}

void GameOver::deInit()
{
	enemiesText->setText("");
	//scoreText->setText("");

	gameOver->setPosition(glm::vec2(-5000, 0));
	deadUshiko->setPosition(glm::vec2(-5000, 0));
}

int GameOver::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	/*glm::vec2 screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());

	touchPosition = glm::vec2(0, 0);
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
		touchPosition = siika->_input->touchPosition(i)._positionStart;

	glm::vec2 box = siika->transfCrds()->deviceToUser(gameOverScreen->getComponent<misc::TransformComponent>()->getPosition());
	if ((touchPosition.x > box.x && touchPosition.x < box.x + screenSize.x) &&
		touchPosition.y > box.y && touchPosition.y < box.y + screenSize.y)*/

	if (deathFrames < 8)
	{
		deathSteps += 1;
		if (deathSteps >= 10)
		{
			deadUshiko->step();
			deathSteps = 0;
			deathFrames += 1;
		}
	}

	if (siika->_input->touchPositionsActive() > 0)
		return MAIN_MENU;

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return GAME_OVER;
}