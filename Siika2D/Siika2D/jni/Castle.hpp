#ifndef CASTLE_H
#define CASTLE_H

#include "../engine/audio/Audio.h"

#include "Scene.hpp"
#include "CastleGenerator.hpp"

class Castle : public Scene
{
public:
	Castle();
	~Castle();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit();

	virtual void pause();
	virtual void resume();

private:
	CastleGenerator *lg;

	colListener *cl;

	audio::Audio *theme;
};

#endif // CASTLE_H