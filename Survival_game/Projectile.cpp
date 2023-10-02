#include "stdafx.h"
#include "helperFuncs.h"
#include "Projectile.h"

Projectile::Projectile(float x, float y, sf::Texture& texture_sheet, objectType _type) : Entity(_type)
{
	this->setTexture(texture_sheet);
	this->setPosition(x, y);
	this->createHitboxComponent(this->sprite, 20.f, 20.f, 88.f, 86.f); //y_offset / 8, x_offset / 3
	this->createMovementComponent(300.0f, 15.0f, 2.0f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("FLY", 20.f, 0, 0, 5, 0, 128, 126);
}

Projectile::~Projectile()
{
}

void Projectile::setTarget(std::shared_ptr<Enemy>& en)
{
	this->target = en;
}

std::shared_ptr<Enemy> Projectile::getTarget() const
{
	if (this->target)
		return this->target;
	return nullptr;
}



void Projectile::updateAnimation(const float& dt)
{
	this->animationComponent->play("FLY", dt);
}

void Projectile::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}

void Projectile::findTarget(std::list<std::shared_ptr<Enemy>>& enemies)
{
	float closest = INT32_MAX;
	std::shared_ptr<Enemy> ent = nullptr;
	for (auto const& obj : enemies)
	{
		if (obj)
		{
			float d = distance(this->getPosition(), obj->getPosition());
			if (closest > d)
			{
				closest = d;
				ent = obj;
			}
		}
	}
	this->setTarget(ent);
}
