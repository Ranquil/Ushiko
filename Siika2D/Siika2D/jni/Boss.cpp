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

	boss->move(glm::vec2(screenSize.x, 0));

	projectileTimer.start();
	bossHealth = bossMaxHealth;
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
	ProjectileType PT;
	
		int projectileType(lrand48() % 4);
		if (projectileType == 0)
			PT = RETURNABLE;
		else
			PT = DAMAGING;
	



	graphics::Texture *pTexture;
	if (PT == RETURNABLE)
		pTexture = siika->_textureManager->createTexture("sprite_inkball.png");
	else if (PT == DAMAGING)
		pTexture = siika->_textureManager->createTexture("panda.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(64, 64),
		glm::vec2(32, 32),
		pTexture,
		glm::vec2(0, 0),
		glm::vec2(1, 1))));
	sprtComp->setZ(20);

	misc::TransformComponent *trnsComp = new misc::TransformComponent;

	go->addComponent(sprtComp);
	go->addComponent(trnsComp);

	glm::vec2 bossPos = siika->transfCrds()->deviceToUser(boss->getComponent<misc::TransformComponent>()->getPosition());
	Projectile *p = new Projectile(go, PT);
	p->xPos = bossPos.x;
	p->yPos = (-screenSize.y / 20) * ((lrand48() % 16 + 2));
	go->move(glm::vec2(p->xPos, p->yPos));
	projectiles.push_back(p);
}

bool Boss::isIntersecting(glm::vec2 projectilePosition, glm::vec2 otherPosition)
{
	if ((projectilePosition.x > otherPosition.x - 64 && projectilePosition.x < otherPosition.x + 64) &&
		projectilePosition.y > otherPosition.y - 64 && projectilePosition.y < otherPosition.y + 64)
		return true;
	return false;
}

void Boss::update(core::Siika2D *siika)
{
	if (projectileTimer.getElapsedTime(MILLISECONDS) >= 1000)
	{
		spawnProjectile(siika);
		projectileTimer.reset();
		bossHealth -= 1;
	}

		glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
		glm::vec2 bossPos = siika->transfCrds()->deviceToUser(boss->getComponent<misc::TransformComponent>()->getPosition());
	Projectile *deletep = nullptr;
	for (Projectile* p : projectiles)
	{
		glm::vec2 pPosition = siika->transfCrds()->deviceToUser(p->gameObject->getComponent<misc::TransformComponent>()->getPosition());
		if ((p->projectileType == DAMAGING || p->projectileType == RETURNABLE) && isIntersecting(pPosition, ushikoPos))
		{
			if (ushiko.dashing)
			{
				if (p->projectileType == RETURNABLE)
				{
					p->pDirection = p->pDirection - p->pDirection * 2;
					p->projectileType = LAST;
				}
				if (p->projectileType == DAMAGING)
				{
					deletep = p;
				}
			}
			else
			{
				ushiko.health -= 1;
				deletep = p;
			}
		}


		if (pPosition.x < 0)
		{
			deletep = p;
		}
		p->gameObject->update();
		p->gameObject->move(glm::vec2(p->xPos -= p->pDirection, p->yPos));
	}
	if (deletep != nullptr)
	{
		projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), deletep), projectiles.end());
		delete deletep;
	}
	boss->update();
}