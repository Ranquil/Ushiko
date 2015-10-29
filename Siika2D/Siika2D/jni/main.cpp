#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"

#include <Box2D/Box2D.h>

#include "Level.hpp"

core::Siika2D *siika = core::Siika2D::UI();
Level *level;

void siika_onPause() {}
void siika_onResume() {}

void siika_init()
{
	level = new Level(siika);
}

void siika_main()
{
	level->update(siika);
}
