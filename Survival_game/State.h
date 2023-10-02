#ifndef STATE_H
#define STATE_H

#pragma once

#include "Player.h"

class State
{
private:

protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;

	bool quit;
	bool pause;

	float keyTime;
	float keyTimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	//ACCESSORS
	const bool& getQuit() const;
	const bool getKeyTime();

	//FUNCTIONS
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateKeyTime(const float& dt);

	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif // !STATE_H