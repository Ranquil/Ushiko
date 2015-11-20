#include "Boss.hpp"
#include "Ushiko.hpp"

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

	screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());

	graphics::Texture *bossTexture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(256, 256),
		glm::vec2(256, 0),
		bossTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(30);

	boss->addComponent(sprtComp);
	boss->addComponent(trnsComp);

	boss->move(glm::vec2(screenSize.x, -screenSize.y / 2));

	projectileTimer.start();
}

void Boss::deInit()
{
	delete boss;
	for (Projectile* p : projectiles)
		delete p;
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
	sprtComp->setZ(20);

	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	ProjectileType PT = static_cast<ProjectileType>(lrand48() % LAST);
	glm::vec2 bossPos = siika->transfCrds()->deviceToUser(boss->getComponent<misc::TransformComponent>()->getPosition());
	Projectile *p = new Projectile(go, PT);
	p->xPos = bossPos.x;
	p->yPos = (-screenSize.y / 20) * (lrand48() % 21);
	go->move(glm::vec2(p->xPos, p->yPos));
	projectiles.push_back(p);
}

void Boss::update(core::Siika2D *siika)
{
	if (projectileTimer.getElapsedTime(MILLISECONDS) >= 500)
	{
		spawnProjectile(siika);
		projectileTimer.reset();
	}


	for (Projectile* p : projectiles)
	{
		glm::vec2 pPosition = p->gameObject->getComponent<misc::TransformComponent>()->getPosition();
		p->gameObject->update();
		p->gameObject->move(glm::vec2(p->xPos -= 7, p->yPos));
		if (pPosition.x < 0)
		{
			delete(p);
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), p), projectiles.end());
		}
	}

	boss->update();
}