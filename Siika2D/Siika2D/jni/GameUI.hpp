#ifndef GAMEUI_H
#define GAMEUI_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/timer.h"
#include "Boss.hpp"

enum UIState
{
	DEFAULT,
	PAUSE,
	RESUME
};

class GameUI
{
public:
	GameUI();
	~GameUI();

	int update(core::Siika2D *siika, Boss *boss = nullptr);

	void init(core::Siika2D *siika, std::string levelName, Boss *boss = nullptr);
	void deInit();

	void changeTexture(misc::GameObject *gameObject, core::Siika2D *siika, std::string newTextureName, glm::vec2 size);

private:
	int heartCount;
	int bossHeartCount;

	UIState lastState;

	graphics::Text *gemTextUI;
	graphics::Sprite *shade;

	graphics::Text *pointsTextUI;

	std::vector<misc::GameObject*> bossHeartIcons;
	misc::GameObject *bossText;
	std::vector<misc::GameObject*> heartIcons;
	misc::GameObject *pauseButton;
	misc::Timer inputTimer;
	glm::vec2 touchPosition;
};

#endif // GAMEUI_H