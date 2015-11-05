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

	pauseButtonTexture = siika->_textureManager->createTexture("ui_pausebutton.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0.5, 0.5),
		glm::vec2(128, 128),
		glm::vec2(0, 0),
		pauseButtonTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;

	pauseButton->addComponent(sprtComp);
	pauseButton->addComponent(transComp);

	lastState = RESUME;
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

	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		touchPosition = siika->_input->touchPosition(i)._positionCurrent;
	}
	if (siika->_input->fingerUp() == true)
	{
		if (isIntersecting(touchPosition, pauseButton->getComponent<misc::TransformComponent>()->getPosition()))
		{
			if (lastState == RESUME)
			{
				lastState = PAUSE;
				return PAUSE;
			}
			else
			{
				lastState = RESUME;
				return RESUME;
			}
		}
	}
	return DEFAULT;


}