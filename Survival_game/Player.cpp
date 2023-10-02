#include "stdafx.h"
#include "Player.h"

bool Player::canAttack()
{
	if (this->attackCooldown <= 0)
		return true;
	return false;
}

//Initializer Functions
void Player::initVariables()
{
	this->attacking = false;
	this->isDead = false;
	this->attackCooldown = 1.f;
}

void Player::initComponents()
{


}


//Constructor / destructor
Player::Player(float x, float y, sf::Texture& texture_sheet, objectType _type) : Entity(_type)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 66.5f, 34.f, 133.f, 204.f); //y_offset / 8, x_offset / 3
	this->createMovementComponent(300.0f, 15.0f, 5.0f);
	this->createAnimationComponent(texture_sheet);

	//this->animationComponent->addAnimation("IDLE_DOWN", 20.f, 0, 9, 1, 9, 261, 276);
	//this->animationComponent->addAnimation("IDLE_UP", 20.f, 0, 8, 2, 8, 261, 276);
	//this->animationComponent->addAnimation("IDLE_LEFT", 20.f, 0, 11, 2, 11, 261, 276);
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 10, 2, 10, 261, 276);

	//this->animationComponent->addAnimation("WALK_LEFT", 15.f, 0, 15, 3, 15, 261, 276);
	this->animationComponent->addAnimation("WALK", 15.f, 0, 14, 3, 14, 261, 276);
	//this->animationComponent->addAnimation("WALK_UP", 15.f, 0, 12, 3, 12, 261, 276);
	//this->animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 13, 3, 13, 261, 276);

	//this->animationComponent->addAnimation("ATTACK_LEFT", 10.f, 0, 3, 4, 3, 261, 276);
	this->animationComponent->addAnimation("ATTACK", 10.f, 0, 2, 4, 2, 261, 276);
	//this->animationComponent->addAnimation("ATTACK_UP", 10.f, 0, 0, 5, 0, 261, 276);
	//this->animationComponent->addAnimation("ATTACK_DOWN", 10.f, 0, 1, 4, 1, 261, 276);

	this->animationComponent->addAnimation("DEAD", 10.f, 0, 5, 4, 5, 261, 276);
}

Player::~Player()
{
}

void Player::setDead(bool dead)
{
	this->isDead = dead;
}

bool Player::getDead()
{
	return this->isDead;
}



//Functions
void Player::updateAttack()
{
	this->attacking = true;
	this->attackCooldown = 1.f;
}

void Player::updateAnimation(const float& dt)
{
	if (this->isDead)
	{
		this->animationComponent->play("DEAD", dt, true, true);
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

	else
	{
		if (this->movementComponent->getState(MOVING_RIGHT))
		{
			if (this->sprite.getScale().x < 0.f) //flip once if need to
			{
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(1.f, 1.f);
			}
		}
		
		else if (this->movementComponent->getState(MOVING_LEFT))
		{
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(258.f, 0.f);
				this->sprite.setScale(-1.f, 1.f);
			}
		}

		this->animationComponent->play("WALK", dt,
				this->movementComponent->getVelocity().x,
				this->movementComponent->getMaxVelocity());	
	}


	/*
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
	*/

}
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	//update attack cooldown timer
	if (this->attackCooldown > 0)
		this->attackCooldown -= dt;
}