#include "GameOver.hpp"

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
	GameOverScreen = new misc::GameObject;

	graphics::Texture *texture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(screenSize.x, screenSize.y),
		glm::vec2(0, 0),
		texture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	GameOverScreen->addComponent(sprtComp);
	GameOverScreen->addComponent(trnsComp);
}

void GameOver::deInit()
{

}

int GameOver::update(core::Siika2D *siika)
{


	return GAME_OVER;
}