#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "../engine/core/Siika2D.h"

class Collectable
{

public:
	Collectable();
	~Collectable();

	void init(core::Siika2D *siika);
	void deinit();
	void update(core::Siika2D *siika);
	bool isIntersecting(glm::vec2 thisPosition, glm::vec2 ushikoPosition);

	misc::GameObject *go;
private:
	glm::vec2 ushikoPosition;
};

#endif //COLLECTABLE_H