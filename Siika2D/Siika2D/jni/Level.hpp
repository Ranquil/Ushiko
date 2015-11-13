#ifndef LEVEL_H
#define LEVEL_H

#include "../engine/audio/Audio.h"

#include "Scene.hpp"
#include "CastleGenerator.hpp"
#include "GameUI.hpp"

class Level : public Scene
{
public:
	Level(std::string name);
	~Level();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual void pause();
	virtual void resume();

private:
	bool paused;
	std::string levelName;

	CastleGenerator *lg;
	colListener *cl;
	GameUI *gameUI;

	audio::Audio *theme;
};

#endif // LEVEL_H