#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    //Variables
    bool isDead;
    bool attacking;
    float attackCooldown;
    int playerHits = 3;
    
    //Initializer functions
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet, objectType);
    virtual ~Player();

    void setDead(bool);
    bool getDead();
    bool canAttack();
    //Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
};

#endif // !PLAYER_H