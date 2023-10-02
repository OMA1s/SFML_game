#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
    //Variables
    bool attacking;
    float attackCooldown;
    int enemyHits = 3;
    bool isDead = false;
    bool noLives = false;

    objectType type;
    //Initializer functions
    void initVariables();
    void initComponents();
public:
	Enemy(float x, float y, sf::Texture& texture_sheet, objectType);
	virtual ~Enemy();

    bool canAttack();
    bool getDead();
    bool noLife();
    void takeHit();
    //Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
};

#endif // !ENEMY_H