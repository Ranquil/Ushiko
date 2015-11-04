#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(core::Siika2D *siika);
	void update(core::Siika2D *siika, colListener *collisions);

	misc::GameObject *go;
	
};

#endif // ENEMY_H