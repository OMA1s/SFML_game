#ifndef MOVEMENT_H
#define MOVEMENT_H

#pragma once


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
enum direction { DOWN = 0, UP, LEFT, RIGHT };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	direction player_dir = DOWN;
	//Initializer functions
public:


	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;

	//Functions
	const bool getState(const short unsigned state);

	const short unsigned getDir() const;

	const bool idle() const;
	const bool moving() const;
	const bool movingLeft() const;
	const bool movingRight() const;

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif // !MOVEMENT_H