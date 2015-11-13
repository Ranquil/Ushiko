#include "Castle.hpp"
#include "Ushiko.hpp"

Castle::Castle()
{

}

Castle::~Castle()
{
	deInit();
}

void Castle::init(core::Siika2D *siika)
{
	lg = new CastleGenerator(siika);
	gameUI = new GameUI;
	gameUI->init(siika);

	ushiko.go->getComponent<misc::PhysicsComponent>()->applyLinearForce(glm::vec2(5, 0));

	glm::vec2 scrSize = siika->_graphicsContext->getDisplaySize();
	bg = siika->_spriteManager->createSprite(
		glm::vec2(0, -scrSize.y),
		glm::vec2(scrSize.x, scrSize.y * 2),
		glm::vec2(0, 0),
		siika->_textureManager->createTexture("background_menu_castle.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1));
	bg->setZ(100);

	theme = siika->_audioManager->createAudio("castle_theme.ogg");
	theme->setLooping(true);
	theme->play();

	cl = new colListener;
	siika->_boxWorld->SetContactListener(cl);

	paused = false;
}

void Castle::deInit()
{
	theme->stop();
	//delete theme;

	bg->setPosition(glm::vec2(-3000, 0));

	delete gameUI;
	delete lg;
	delete cl;
}

int Castle::update(core::Siika2D *siika)
{
	siika->_graphicsContext->clear();

	int state = gameUI->update(siika);
	if (state == PAUSE)
		pause();
	else if (state == RESUME)
		resume();

	if (!paused)
	{
		siika->_boxWorld->Step(1.5f / 60.0f, 6, 2);

		lg->update(siika);
		ushiko.update(siika);
	}

	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();

	if (ushiko.health <= 0)
		return MAIN_MENU;
	return CASTLE_LEVEL;
}

void Castle::pause()
{
	gameUI->lt->levelTimer.pause();
	theme->pause();
	paused = true;
}

void Castle::resume()
{
	gameUI->lt->levelTimer.resume();
	theme->play();
	paused = false;
}