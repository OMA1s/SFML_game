#ifndef ENDGAME_SCREEN_H
#define ENDGAME_SCREEN_H
#pragma once

#include "Button.h"

class EndGameScreen
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

	//

public:
	EndGameScreen(sf::RenderWindow& window, sf::Font& font);
	virtual ~EndGameScreen();

	//ACCESSORS
	std::map<std::string, Button*>& getButtons();

	//FUNCTIONS
	const bool isButtonPressed(const std::string key);

	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f&);
	void render(sf::RenderTarget& target);
};


#endif // !ENDGAME_SCREEN_H