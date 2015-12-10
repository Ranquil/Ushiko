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
	glm::vec2 screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());
	gameOverScreen = new misc::GameObject;

	graphics::Texture *texture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(screenSize.x, screenSize.y),
		glm::vec2(0, 0),
		texture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	gameOverScreen->addComponent(sprtComp);
	gameOverScreen->addComponent(trnsComp);

	enemiesText = siika->_textManager->createText();
	enemiesText->setFont("coolvetica.ttf");
	enemiesText->setPosition(-0.5f, -0.4f);
	enemiesText->setFontSize(64);

	std::stringstream enm;
	enm << "Enemies killed: " << ushiko.enemiesKilled;
	enemiesText->setText(enm.str());

	scoreText = siika->_textManager->createText();
	scoreText->setFont("coolvetica.ttf");
	scoreText->setPosition(-0.5f, -0.2f);
	scoreText->setFontSize(64);

	std::stringstream scr;
	scr << "Total score: " << ushiko.pointsAmount;
	scoreText->setText(scr.str());
}

void GameOver::deInit()
{
	enemiesText->setText("");
	scoreText->setText("");

	delete gameOverScreen;
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

	if (siika->_input->touchPositionsActive() > 0)
		return MAIN_MENU;

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	return GAME_OVER;
}