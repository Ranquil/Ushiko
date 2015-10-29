#include "../engine/core/Siika2D.h"

#include <Box2D/Box2D.h>

#include "Level.hpp"

core::Siika2D *siika = core::Siika2D::UI();
int screenState;

void siika_onPause() {}
void siika_onResume() {}

Scene scenes[3];

void siika_init()
{
	screenState = GAME_LEVEL;

	scenes[GAME_LEVEL] = new Level(siika);
}

void siika_main()
{
	screenState = scenes[screenState].update(siika);
}
