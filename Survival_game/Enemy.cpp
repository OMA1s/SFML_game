#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	
}

void Enemy::initComponents()
{
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, objectType _type) : Entity(_type), attackCooldown(1.f)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);
	

	this->createHitboxComponent(this->sprite, 50.f, 100.f, 150.f, 75.f); //y_offset / 8, x_offset / 3
	this->createMovementComponent(100.0f, 15.0f, 5.0f);
	this->createAnimationComponent(texture_sheet);
	if (_type == objectType::skeleton)
	{
		this->animationComponent->addAnimation("IDLE", 20.f, 0, 5, 2, 5, 260, 260); //previous w, h, 260
		this->animationComponent->addAnimation("WALK", 15.f, 0, 7, 3, 7, 260, 260);
		this->animationComponent->addAnimation("ATTACK", 20.f, 0, 1, 4, 1, 260, 260);
		this->animationComponent->addAnimation("DEAD", 20.f, 0, 3, 4, 3, 260, 260);
		//std::cout << "ANIMATIONS ADDED" << std::endl;
	}
	else
	{
		std::cout << "ANIMATIONS NOT ADDED" << std::endl;
	}
		
}

Enemy::~Enemy()
{
	//std::cout << "Enemy destroyed" << std::endl;
}

bool Enemy::canAttack()
{
	if (this->attackCooldown <= 0)
		return true;
	return false;
}

bool Enemy::getDead()
{
	return this->isDead;
}

bool Enemy::noLife()
{
	return this->noLives;
}

void Enemy::takeHit()
{
	if (this->enemyHits > 0)
		this->enemyHits -= 1;
}

void Enemy::updateAttack()
{
	this->attacking = true;
}

void Enemy::updateAnimation(const float& dt)
{
	if (this->noLives)
	{
		if (this->animationComponent->play("DEAD", dt, true, true))
			this->isDead = true;
		return;
	}
	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}
	
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f) //flip once if need to
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt,
										this->movementComponent->getVelocity().x,
										this->movementComponent->getMaxVelocity());
	}

	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt,
										this->movementComponent->getVelocity().x,
										this->movementComponent->getMaxVelocity());
	}



	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt,
										this->movementComponent->getVelocity().y,
										this->movementComponent->getMaxVelocity());
	}

	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt,
										this->movementComponent->getVelocity().y,
										this->movementComponent->getMaxVelocity());
	}
}

void Enemy::update(const float& dt)
{
	if (this->enemyHits < 1)
		this->noLives = true;
	this->movementComponent->update(dt);
	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
	if (this->attackCooldown > 0)
		this->attackCooldown -= dt;
}
