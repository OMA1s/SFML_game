#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include "State.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Map.h"

class GameState : public State
{
private:
    float timeElapsed = 0.f;
    float vectorRefresh = 0.f;

    sf::Font font;

    Player* player;
    sf::Texture texture;

    std::list<std::shared_ptr<Enemy>> enemies;
    std::list<Projectile*> projectiles;
    //TileMap* tileMap;
    Map* gameMap;

    //window bounds
    int windowWidth;
    int windowHeight;

    //Functions
    void initMap();
    void initTextures();
    void initPlayers();
    void initFonts();
    void initEnemy();
    void initProjectile(Projectile*);

    void updateTime(const float& dt);
    void garbageCollect();

public:
    GameState(sf::RenderWindow*, std::stack<State*>*);
    virtual ~GameState();

    //Functions
    void createEnemy();

    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updateEnemyInput(const float& dt);

    void createProjectile(float x, float y);
    void deleteProjectile();
    void updateProjectileInput(const float dt);

    void update(const float&);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !GAMESTATE_H
