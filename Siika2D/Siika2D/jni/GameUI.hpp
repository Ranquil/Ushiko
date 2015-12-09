#ifndef GAMEUI_H
#define GAMEUI_H

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

	void init(core::Siika2D *siika, std::string levelName, Boss *boss = nullptr);
	void deInit();

	int update(core::Siika2D *siika, Boss *boss = nullptr);

private:
	void changeTexture(misc::GameObject *gameObject, core::Siika2D *siika, std::string newTextureName, glm::vec2 size);

	int heartCount;
	int bossHeartCount;

	UIState lastState;

	std::vector<misc::GameObject*> heartIcons;
	std::vector<misc::GameObject*> bossHeartIcons;

	graphics::Text *pointsTextUI;
	graphics::Sprite *shade;
	misc::GameObject *bossText;
	misc::GameObject *pauseButton;
	misc::Timer inputTimer;
	int levelPoints;
};

#endif // GAMEUI_H