#include "Boss.hpp"

Boss::Boss()
{

}

Boss::~Boss()
{
	deInit();
}

void Boss::init(core::Siika2D *siika)
{
	boss = new misc::GameObject;

	graphics::Texture *bossTexture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(256, 256),
		glm::vec2(128, 128),
		bossTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(30);

	boss->addComponent(sprtComp);
	boss->addComponent(trnsComp);

	projectileTimer.start();
}

void Boss::deInit()
{
	delete boss;
	for (Projectile* p : projectiles)
	{
		delete p;
	}
}

void Boss::spawnProjectile(core::Siika2D *siika)
{
	misc::GameObject *go = new misc::GameObject;

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		siika->_textureManager->createTexture("panda.png"),
		glm::vec2(0, 0),
		glm::vec2(1, 1))));

	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	projectiles.push_back(new Projectile(go, RETURNABLE));
}

void Boss::update(core::Siika2D *siika)
{
	if (projectileTimer.getElapsedTime(MILLISECONDS) >= 500)
	{
		spawnProjectile(siika);
	}

	for (Projectile* p : projectiles)
	{
		glm::vec2 *pPosition = &p->gameObject->getComponent<misc::TransformComponent>()->getPosition();
		p->gameObject->update();
		p->gameObject->move(glm::vec2(pPosition->x -= 7, pPosition->y));
	}

	boss->update();
}