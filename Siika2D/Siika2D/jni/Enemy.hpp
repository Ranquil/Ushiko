#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"

class Enemy
{
public:
	Enemy(std::string enemyTextureName);
	~Enemy();

	void init(core::Siika2D *siika);
	void deInit(core::Siika2D *siika);
	void update(core::Siika2D *siika);

	misc::GameObject *go;
	std::string enemyTextureName;
	
};

#endif // ENEMY_H