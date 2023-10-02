#ifndef GAME_H
#define GAME_H
#pragma once

#include "MainMenuState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	void initVariables();
	void initWindow();
	void initStates();

public:
	//Constructor/destructir
	Game();
	virtual ~Game();

	//update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Functions
	void run();
	void render();
	void endApplication();
};


#endif // !GAME_H