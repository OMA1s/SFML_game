#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

enum objectType { player, skeleton, ghost, inanimate };
class Entity
{
private:
	void initVariables();
protected:
	objectType type;
	sf::Sprite sprite;
	//sf::Texture* texture;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

public:
	Entity(objectType);
	virtual ~Entity();

	//Component Functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
		float width, float height);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void setPosition(const float y, const float x);
	virtual const sf::Vector2f getPosition();

	virtual void move(const float x, const float y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

	virtual bool checkCollision(const Entity& other);
};

#endif // !ENTITY_H