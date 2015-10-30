#ifndef CASTLE
#define CASTLE

#include "Scene.hpp"
#include "CastleGenerator.hpp"
#include "LevelTimer.hpp"

class Castle : public Scene
{
public:
	Castle();
	~Castle();

	virtual int update(core::Siika2D *siika);

	virtual void init(core::Siika2D *siika);
	virtual void deInit(core::Siika2D *siika);

private:
	misc::GameObject ushiko;
	//glm::vec2 position;
	CastleGenerator *lg;
	LevelTimer *lt;
	colListener collisionListener;

	misc::Timer tempTimer;
	bool canJump;
};

#endif // CASTLE