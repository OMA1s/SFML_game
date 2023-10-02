#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	//this->texture = nullptr;
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
		
}

Entity::Entity(objectType _type) : type(_type)
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

//Component Functions
void Entity::setTexture(sf::Texture& texture)
{
	//this->texture = &texture;
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Functions
void Entity::setPosition(const float y, const float x)
{
	this->sprite.setPosition(x, y);
}

const sf::Vector2f Entity::getPosition()
{
	return this->sprite.getPosition();
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
		//this->sprite.move(this->movementComponent->getVelocity() * dt); //Uses velocity
	}

}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hitboxComponent)
		hitboxComponent->render(target);
}

bool Entity::checkCollision(const Entity& other)
{
	return (this->hitboxComponent->checkIntersect(other.hitboxComponent->getRect()));
}
