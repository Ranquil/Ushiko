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
	bossFront = new misc::GameObject;

	screenSize = siika->transfCrds()->deviceToUser(siika->_graphicsContext->getDisplaySize());

	graphics::Texture *bossTexture = siika->_textureManager->createTexture("sprite_tentacles_front.png");

	misc::SpriteComponent *sprtComp = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(768, 768),
		glm::vec2(768, 384),
		bossTexture,
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5))));
	misc::TransformComponent *trnsComp = new misc::TransformComponent;
	sprtComp->setZ(90);

	bossFront->addComponent(sprtComp);
	bossFront->addComponent(trnsComp);

	bossFront->move(glm::vec2(screenSize.x, -screenSize.y / 2));
	bossBack = new misc::GameObject;

	graphics::Texture *bossTexture2 = siika->_textureManager->createTexture("sprite_tentacles_back.png");

	misc::SpriteComponent *sprtComp2 = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(768, 768),
		glm::vec2(768, 384),
		bossTexture2,
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5))));
	misc::TransformComponent *trnsComp2 = new misc::TransformComponent;
	sprtComp->setZ(0);

	bossBack->addComponent(sprtComp2);
	bossBack->addComponent(trnsComp2);

	bossBack->move(glm::vec2(screenSize.x, -screenSize.y / 2));

	projectileTimer.start();
	animTimer.start();
	bossHealth = bossMaxHealth;
}

void Boss::deInit()
{
	delete bossFront;
	delete bossBack;
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
	pTexture = siika->_textureManager->createTexture("sprite_inkball.png");

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

	glm::vec2 bossPos = siika->transfCrds()->deviceToUser(bossFront->getComponent<misc::TransformComponent>()->getPosition());
	Projectile *p = new Projectile(go, PT);
	if (PT == DAMAGING)
		p->gameObject->getComponent<misc::SpriteComponent>()->getSprite()->setColor(graphics::Color(255, 0, 0, 255));
	p->xPos = bossPos.x;
	p->yPos = (-screenSize.y / 20) * ((lrand48() % 16 + 2));
	go->move(glm::vec2(p->xPos, p->yPos));
	projectiles.push_back(p);
}

bool Boss::isIntersecting(glm::vec2 projectilePosition, glm::vec2 otherPosition)
{
	int test = 84;
	if ((projectilePosition.x > otherPosition.x- test && projectilePosition.x < otherPosition.x + test) &&
		projectilePosition.y > otherPosition.y - test && projectilePosition.y < otherPosition.y + test)
		return true;
	return false;
}

void Boss::update(core::Siika2D *siika)
{
	if (projectileTimer.getElapsedTime(MILLISECONDS) >= 1000)
	{
		spawnProjectile(siika);
		projectileTimer.reset();
	}

	glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
	glm::vec2 bossPos = siika->transfCrds()->deviceToUser(bossFront->getComponent<misc::TransformComponent>()->getPosition());
	Projectile *deletep = nullptr;
	for (Projectile* p : projectiles)
	{
		glm::vec2 pPosition = siika->transfCrds()->deviceToUser(p->gameObject->getComponent<misc::TransformComponent>()->getPosition());
		if ((p->projectileType == DAMAGING || p->projectileType == RETURNABLE) && isIntersecting(pPosition, ushikoPos))
		{
			if (ushiko.dashing && p->projectileType == RETURNABLE)
			{
				p->pDirection = p->pDirection - p->pDirection * 2;
				p->projectileType = LAST;
			
			}
			else
			{
				ushiko.health -= 1;
				deletep = p;
			}
		}
		if (pPosition.x > screenSize.x && p->projectileType == LAST)
		{
			bossHealth -= 1;
			deletep = p;
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
	bossFront->update();
	bossBack->update();
	if (animTimer.getElapsedTime(MILLISECONDS) >= 100)
	{
		bossFront->getComponent<misc::SpriteComponent>()->getSprite()->step();
		bossBack->getComponent<misc::SpriteComponent>()->getSprite()->step();
		animTimer.reset();
	}
}