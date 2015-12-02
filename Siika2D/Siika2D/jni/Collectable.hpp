#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "../engine/core/Siika2D.h"
#include "../engine/misc/GameObject.h"
#include "../engine/misc/Timer.h"

enum CoinType
{
	BRONZE,
	SILVER,
	GOLD
};

class Collectable
{
public:
	Collectable();
	~Collectable();

	void init(core::Siika2D *siika, bool isHeart = false);
	void deinit();

	void update();

	int xPos, yPos;
	misc::GameObject *go;
	CoinType coinType;
	bool isHeart;

private:
	misc::Timer animTimer;
};

#endif //COLLECTABLE_H