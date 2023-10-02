#include "stdafx.h"
#include "InstructionsState.h"

void InstructionsState::initInstructions()
{
	float textBoxWidth = 500.f;
	float textBoxHeight = 500.f;
	std::string message = "USE ARROW KEYS TO MOVE.\nPRESS SPACEBAR TO ATTACK.\nSURVIVE AS LONG AS YOU CAN!";

	this->textBox.setPosition(sf::Vector2f(100, 100));
	this->textBox.setSize(sf::Vector2f(textBoxWidth, textBoxHeight));
	this->textBox.setFillColor(sf::Color::Transparent);
	this->textBox.setOutlineThickness(1.f);
	this->textBox.setOutlineColor(sf::Color::White);

	this->font = font;
	this->instructionsMessage.setFont(this->font);
	this->instructionsMessage.setString(message);
	this->instructionsMessage.setFillColor(sf::Color::White);
	this->instructionsMessage.setCharacterSize(50);

	//set text in middle
	this->instructionsMessage.setPosition(
		(this->textBox.getPosition().x + (this->textBox.getGlobalBounds().width / 2.0f)) - (this->instructionsMessage.getGlobalBounds().width / 2.0f),
		(this->textBox.getPosition().y + (this->textBox.getGlobalBounds().height / 2.0f)) - (this->instructionsMessage.getGlobalBounds().height / 2.0f)
	);
}

void InstructionsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Assets/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void InstructionsState::initFont()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void InstructionsState::initButtons()
{
	this->backButton = new Button(
		1500, 880, 250, 50,
		&this->font, "BACK", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

InstructionsState::InstructionsState(sf::RenderWindow* _window, std::stack<State*>* _states) : State(_window, _states)
{
	this->initBackground();
	this->initInstructions();
	this->initFont();
	this->initButtons();
}

InstructionsState::~InstructionsState()
{
	delete this->backButton;
}

void InstructionsState::updateInput(const float& dt)
{
}

void InstructionsState::updateButtons()
{
	this->backButton->update(this->mousePosView);

	if (this->backButton->isPressed())
	{
		this->endState();
	}
}

void InstructionsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void InstructionsState::renderButtons(sf::RenderTarget& target)
{
	this->backButton->render(target);
}

void InstructionsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(textBox);
	target->draw(instructionsMessage);

	this->renderButtons(*target);
}
