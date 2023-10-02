#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->id = id;
	this->buttonState = BTN_IDEL;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);


	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);

	//set text in middle
	this->text.setPosition(
		(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f)) - (this->text.getGlobalBounds().width / 2.0f),
		(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f)) - (this->text.getGlobalBounds().height / 2.0f)
	);
	//this->text.setString(text);

	this->textIdleColor = text_idle_color;
	this->textActiveColor = text_active_color;
	this->textHoverColor = text_hover_color;

	this->idleColor = idle_color;
	this->activeColor = active_color;
	this->hoverColor = hover_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineActiveColor = outline_active_color;
	this->outlineHoverColor = outline_hover_color;
}

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}
const std::string Button::getText() const
{
	return this->text.getString();
}

const short unsigned& Button::getID() const
{
	return this->id;
}


//MODIFIERS
void Button::setText(const std::string text)
{
	this->text.setString(text);
}

//Functions

void Button::setId(const short unsigned id)
{
	this->id = id;
}

void Button::update(const sf::Vector2f& mousePos)
{
	// update the booleans for hover and pressed

	//idle
	this->buttonState = BTN_IDEL;
	//hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDEL:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
