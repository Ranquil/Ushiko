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

void GameUI::init(core::Siika2D *siika, std::string levelName, Boss *boss)
{
	/* ----- Initialize the pause button ----- */

	pauseButton = new misc::GameObject;
	graphics::Texture *pauseButtonTexture;
	glm::vec2 scrSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());

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

	pauseButton->move(glm::vec2(scrSize.x - 256, 0));

	/* ----- Initialize hearts ----- */

	graphics::Texture *heartTexture;
	heartTexture = siika->_textureManager->createTexture("ui_heart_pink.png");

	for (int i = 0; i < 3; i++)
	{
		heartIcons.push_back(new misc::GameObject);
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

	/* ----- Initialize the boss stuff ----- */

	if (levelName == "boss")
	{
		graphics::Texture *bossTextTexture;
		bossTextTexture = siika->_textureManager->createTexture("ui_bosslifebar_logo.png");
		bossText = new misc::GameObject;

		misc::SpriteComponent *bosstextsprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
			glm::vec2(0, 0),
			glm::vec2(128, 128),
			glm::vec2(0, 128),
			bossTextTexture,
			glm::vec2(0, 0),
			glm::vec2(1, 1))));
		bosstextsprtComp->setZ(10);

		misc::TransformComponent *bosstexttransComp = new misc::TransformComponent;

		bossText->addComponent(bosstextsprtComp);
		bossText->addComponent(bosstexttransComp);

		bossText->move(glm::vec2(0, -scrSize.y - 32));

		graphics::Texture *bossHeartTexture;
		bossHeartTexture = siika->_textureManager->createTexture("ui_bosslifebar_heart.png");

			for (int i = 0; i < boss->bossMaxHealth; i++)
			{
				bossHeartIcons.push_back(new misc::GameObject);

				misc::SpriteComponent *bossheartsprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
					glm::vec2(0, 0),
					glm::vec2(64, 64),
					glm::vec2(0, 0),
					bossHeartTexture,
					glm::vec2(0, 0),
					glm::vec2(1, 1))));
					bossheartsprtComp->setZ(10);

				misc::TransformComponent *bosshearttransComp = new misc::TransformComponent;

				bossHeartIcons[i]->addComponent(bossheartsprtComp);
				bossHeartIcons[i]->addComponent(bosshearttransComp);
				glm::vec2 heartPos =glm::vec2(256 + i * 96, -scrSize.y + 234);
				bossHeartIcons[i]->move(heartPos);
			}
	}
	else bossText = nullptr;

	/* ----- Initialize other objects and variables ----- */

	shade = siika->_spriteManager->createSprite(
		glm::vec2(0, scrSize.y),
		glm::vec2(scrSize.x, scrSize.y),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("shade.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	shade->setZ(-10);

	ushiko.coinCount = 0;
	if (levelName != "boss")
	{
		pointsTextUI = siika->_textManager->createText();
		pointsTextUI->setFont("coolvetica.ttf");
		pointsTextUI->setPosition(-1, 0.70);
		pointsTextUI->setFontSize(64);
	}
	else pointsTextUI = nullptr;
	lastState = RESUME;
	inputTimer.start();
	heartCount = ushiko.health;

	if (levelName == "boss")
		bossHeartCount = boss->bossHealth;

	if (levelName == "plains")
		levelPoints = 500;
	else if (levelName == "forest")
		levelPoints = 1000;
	else if (levelName == "castle")
		levelPoints = 2000;
}

void GameUI::deInit()
{
	delete pauseButton;

	if (pointsTextUI != nullptr)
		pointsTextUI->setText("");

	for (int i = 0; i < 3; i++)
		delete heartIcons[i];

	if (bossHeartIcons.size() > 0)
	{
		for (int i = 0; i < 10; i++)
			delete bossHeartIcons[i];
	}
	if (bossText != nullptr)
		delete bossText;
}

bool isIntersecting(glm::vec2 touchPosition, glm::vec2 box)
{
	if ((touchPosition.x > box.x && touchPosition.x < box.x + 128) &&
		(touchPosition.y > box.y && touchPosition.y < box.y + 128))
		return true;
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

int GameUI::update(core::Siika2D *siika, Boss *boss)
{

	if (ushiko.health < heartCount)
		changeTexture(heartIcons[ushiko.health], siika, "ui_heart_hurt.png",glm::vec2(64,64));
	else if (ushiko.health > heartCount)
		changeTexture(heartIcons[ushiko.health - 1], siika, "ui_heart_pink.png", glm::vec2(64, 64));

	heartCount = ushiko.health;

	if (boss != nullptr && boss->bossHealth != bossHeartCount)
	{
		changeTexture(bossHeartIcons[boss->bossHealth], siika, "ui_bosslifebar_hearthurt.png", glm::vec2(64, 64));
		bossHeartCount = boss->bossHealth;
	}
	if (boss == nullptr)
	{
		std::stringstream pointsText;
		pointsText << ushiko.pointsAmount << "/" << levelPoints;
		pointsTextUI->setText(pointsText.str());
	}

	glm::vec2 touchPosition = glm::vec2(0, 0);
	if (inputTimer.getElapsedTime(SECONDS) > 0.5)
	{
		for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
			touchPosition = siika->_input->touchPosition(i)._positionStart;
		
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