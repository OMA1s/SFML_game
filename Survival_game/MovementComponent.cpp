#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,
	float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}



//Functions
const bool MovementComponent::getState(const short unsigned state)
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
		{
			return true;
		}
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
		{
			return true;
		}
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
		{
			return true;
		}
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

const short unsigned MovementComponent::getDir() const
{
	return this->player_dir;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Accelerating sprite until it reaches max velocity*/

	//acceleration
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	/*
	Decelerates the sprite and controls maximum velocity.
	Moves the sprite.
	*/
	if (this->velocity.x > 0.0f) //check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.0f)
			this->velocity.x = 0.0f;
	}
	else if (this->velocity.x < 0.0f) //check for negative x
	{
		//Max velocity check negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.0f)
			this->velocity.x = 0.0f;
	}

	if (this->velocity.y > 0.0f) //check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.0f)
			this->velocity.y = 0.0f;
	}
	else if (this->velocity.y < 0.0f) //check for negative y
	{
		//Max velocity check negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.0f)
			this->velocity.y = 0.0f;
	}


	//Final move
	this->sprite.move(this->velocity * dt); //uses velocity
}
