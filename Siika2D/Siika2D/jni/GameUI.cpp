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
	pauseButton = new misc::GameObject;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);
	gemCount = 0;
	gemTextUI = siika->_textManager->createText();
	gemTextUI->setFont("arial.ttf");
	gemTextUI->setPosition(-0.95, -0.95);
	gemTextUI->setFontSize(64);

	graphics::Texture *pauseButtonTexture;

	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	shade = siika->_spriteManager->createSprite(
		glm::vec2(0, scrSize.y),
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("shade.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	shade->setZ(-10);

	pauseButtonTexture = siika->_textureManager->createTexture("ui_pausebutton.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0.5, 0.5),
		glm::vec2(128, 128),
		glm::vec2(0, 0),
		pauseButtonTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;
	sprtComp->setZ(10);

	pauseButton->addComponent(sprtComp);
	pauseButton->addComponent(transComp);

	lastState = RESUME;
	inputTimer.start();
}

void GameUI::deInit()
{
	delete lt;
}

bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + 128) &&
		touchPosition.y > box.y && touchPosition.y < box.y + 128)
	{
		return true;
	}
	return false;
}

int GameUI::update(core::Siika2D *siika)
{
	lt->update();

	std::ostringstream gemText;
	gemText << gemCount << " / " << maxGems;
	gemTextUI->setText(gemText.str());

	touchPosition = glm::vec2(0, 0);

	if (inputTimer.getElapsedTime(SECONDS) > 0.5)
	{
		for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
			touchPosition = siika->_input->touchPosition(i)._positionCurrent;

		if (isIntersecting(touchPosition, pauseButton->getComponent<misc::TransformComponent>()->getPosition()))
		{
			inputTimer.reset();

			if (lastState == RESUME)
			{
				shade->setPosition(glm::vec2(0, 0));
				lastState = PAUSE;
				return PAUSE;
			}
			else
			{
				shade->setPosition(glm::vec2(0, siika->_graphicsContext->getDisplaySize().y));
				lastState = RESUME;
				return RESUME;
			}
		}
	}
	return DEFAULT;


}