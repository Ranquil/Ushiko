#include "GameUI.hpp"
#include "Ushiko.hpp"
#include <sstream>


GameUI::GameUI()
{

}

GameUI::~GameUI()
{
	deInit();
}

void GameUI::init(core::Siika2D *siika)
{
	lt = new LevelTimer;
	lt->InitTimer(siika, "arial.ttf", 64, 0.5, -0.95);
	gemCount = 0;
	gemTextUI = siika->_textManager->createText();
	gemTextUI->setFont("arial.ttf");
	gemTextUI->setPosition(-0.95, -0.95);
	gemTextUI->setFontSize(64);

	pauseButton = new misc::GameObject;
	graphics::Texture *pauseButtonTexture;
	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();

	pauseButtonTexture = siika->_textureManager->createTexture("ui_pausebutton.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(128, 128),
		glm::vec2(0, 0),
		pauseButtonTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *transComp = new misc::TransformComponent;
	sprtComp->setZ(0);

	pauseButton->addComponent(sprtComp);
	pauseButton->addComponent(transComp);

	pauseButton->move(glm::vec2(scrSize.x + scrSize.x / 2, 0));



	graphics::Texture *heartTexture;
	heartTexture = siika->_textureManager->createTexture("ui_heart_full.png");

	heartIcons.push_back(new misc::GameObject);
	heartIcons.push_back(new misc::GameObject);
	heartIcons.push_back(new misc::GameObject);

	for (int i = 0; i < 3; i++)
	{
		misc::SpriteComponent *heartsprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			glm::vec2(0, 0),
			glm::vec2(64, 64),
			glm::vec2(0, 0),
			heartTexture,
			glm::vec2(0, 0),
			glm::vec2(1, 1))));
		misc::TransformComponent *hearttransComp = new misc::TransformComponent;
		heartsprtComp->setZ(10);

		heartIcons[i]->addComponent(heartsprtComp);
		heartIcons[i]->addComponent(hearttransComp);
		
		heartIcons[i]->move(glm::vec2(i * 128, 0));
		heartIcons[i]->update();
	}


	shade = siika->_spriteManager->createSprite(
		glm::vec2(0, scrSize.y),
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("shade.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	shade->setZ(-10);

	lastState = RESUME;
	inputTimer.start();
	heartCount = ushiko.health;
}

void GameUI::deInit()
{
	delete lt;
	delete pauseButton;
	gemTextUI->setText("");
	for (int i = 0; i < 3; i++)
	{
		delete heartIcons[i];
	}
}

bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + 128) &&
		(touchPosition.y > box.y && touchPosition.y < box.y + 128))
	{
		return true;
	}
	return false;
}

void GameUI::changeTexture(misc::GameObject *gameObject, core::Siika2D *siika, std::string newTextureName, glm::vec2 size)
{
	gameObject->removeComponent<misc::SpriteComponent>();
	graphics::Texture *newTexture = siika->_textureManager->createTexture(newTextureName);
	glm::vec2 location = gameObject->getComponent<misc::TransformComponent>()->getPosition();
	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		location,
		size,
		glm::vec2(0, 0),
		newTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	sprtComp->setZ(0);

	gameObject->addComponent(sprtComp);

}

int GameUI::update(core::Siika2D *siika)
{
	if (ushiko.health != heartCount)
	{
		changeTexture(heartIcons[ushiko.health], siika, "ui_heart_hurt.png",glm::vec2(64,64));
	}
	heartCount = ushiko.health;
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
				changeTexture(pauseButton, siika, "ui_playbutton.png", glm::vec2(128,128));
				shade->setPosition(glm::vec2(0, 0));
				lastState = PAUSE;
				return PAUSE;
			}
			else
			{
				changeTexture(pauseButton, siika, "ui_pausebutton.png", glm::vec2(128, 128));
				shade->setPosition(glm::vec2(0, siika->_graphicsContext->getDisplaySize().y));
				lastState = RESUME;
				return RESUME;
			}
		}
	}
	return DEFAULT;


}