#include "Boss.hpp"
#include "Ushiko.hpp"
#include "Sound.hpp"

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

	graphics::Texture *bossTexture = siika->_textureManager->createTexture("sprite_tentaclespink_front.png");

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

	bossFront->move(glm::vec2(screenSize.x + 256, -screenSize.y / 2));
	bossBack = new misc::GameObject;

	graphics::Texture *bossTexture2 = siika->_textureManager->createTexture("sprite_tentaclespink_back.png");

	misc::SpriteComponent *sprtComp2 = new misc::SpriteComponent(misc::SpriteComponent(siika->_spriteManager->createSprite(
		glm::vec2(0, 0),
		glm::vec2(768, 768),
		glm::vec2(768, 384),
		bossTexture2,
		glm::vec2(0, 0),
		glm::vec2(0.5, 0.5))));
	misc::TransformComponent *trnsComp2 = new misc::TransformComponent;
	sprtComp->setZ(10);

	bossBack->addComponent(sprtComp2);
	bossBack->addComponent(trnsComp2);

	bossBack->move(glm::vec2(screenSize.x + 256, -screenSize.y / 2));

	tempY = -screenSize.y / 2;

	projectileTimer.start();
	animTimer.start();
	bossHealth = bossMaxHealth;

	sound.playSound(LONKERO);
}

void Boss::deInit()
{
	sound.stopSound(LONKERO);

	delete bossFront;
	delete bossBack;
	for (Projectile* p : projectiles)
		delete p;
}

void Boss::spawnProjectile(core::Siika2D *siika)
{
	misc::GameObject *go = new misc::GameObject;
	ProjectileType PT;
	
		int projectileType(lrand48() % 3);
		if (projectileType == 0)
			PT = RETURNABLE;
		else
			PT = DAMAGING;

	graphics::Texture *pTexture;
	if (PT == DAMAGING)
		pTexture = siika->_textureManager->createTexture("sprite_inkball.png");
	else
		pTexture = siika->_textureManager->createTexture("sprite_inkballpink.png");

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
	p->xPos = bossPos.x;
	p->yPos = (-screenSize.y / 20) * ((lrand48() % 16 + 2));
	go->move(glm::vec2(p->xPos, p->yPos));
	projectiles.push_back(p);
}

bool Boss::isIntersecting(glm::vec2 projectilePosition, glm::vec2 otherPosition)
{
	int test = 84;
	if (projectilePosition.x < otherPosition.x && projectilePosition.x > otherPosition.x - 100 &&
		projectilePosition.y < otherPosition.y + 200 && projectilePosition.y > otherPosition.y - 200)
		return true;
	return false;
}

void Boss::update(core::Siika2D *siika)
{
	if (projectileTimer.getElapsedTime(MILLISECONDS) >= 2000)
	{
		spawnProjectile(siika);
		projectileTimer.reset();
	}

	glm::vec2 ushikoPos = siika->transfCrds()->deviceToUser(ushiko.go->getComponent<misc::TransformComponent>()->getPosition());
	glm::vec2 bossPos = siika->transfCrds()->deviceToUser(bossFront->getComponent<misc::TransformComponent>()->getPosition());
	glm::vec2 bossBackPos = siika->transfCrds()->deviceToUser(bossBack->getComponent<misc::TransformComponent>()->getPosition());
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
				if (ushiko.health > 0)
					sound.playSound(USHIKO_HURT);
				else sound.playSound(KUOLONKORINA);
				deletep = p;
			}
		}
		if (pPosition.x > screenSize.x && p->projectileType == LAST)
		{
			sound.playSound(BOSS_DAMAGE);
			ushiko.pointsAmount += 100;
			bossHealth -= 1;
			deletep = p;
		}

		if (pPosition.x < 0)
		{
			deletep = p;
		}
		p->gameObject->update();
		p->gameObject->move(glm::vec2(p->xPos -= p->pDirection * 1.5, p->yPos));
	}
	if (deletep != nullptr)
	{
		projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), deletep), projectiles.end());
		delete deletep;
	}
	bossFront->update();
	bossBack->update();
	bossFront->move(glm::vec2(bossPos.x -= bossDirection, tempY));
	bossBack->move(glm::vec2(bossBackPos.x -= (bossDirection - 1), tempY));
	if (bossPos.x < screenSize.x || bossPos.x > screenSize.x + 512)
	{
		bossDirection = -bossDirection;
	}
	if (animTimer.getElapsedTime(MILLISECONDS) >= 100)
	{
		bossFront->getComponent<misc::SpriteComponent>()->getSprite()->step();
		bossBack->getComponent<misc::SpriteComponent>()->getSprite()->step();
		animTimer.reset();
	}
}