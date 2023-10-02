#ifndef BUTTON_H
#define BUTTON_H

#pragma once

enum button_states
{
	BTN_IDEL = 0, BTN_HOVER, BTN_ACTIVE
};

class Button
{
private:
	short unsigned buttonState;
	short unsigned id;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
		short unsigned id = 0);
	~Button();

	//Accessors
	const bool isPressed() const;
	const std::string getText() const;
	const short unsigned& getID() const;

	//MODIFIERS
	void setText(const std::string text);
	void setId(const short unsigned id);

	//Functions
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};


#endif // !BUTTON_H