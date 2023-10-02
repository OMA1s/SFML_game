#include "stdafx.h"
#include "State.h"

//CONSTRUCTOR / DESTRUCTOR
State::State(sf::RenderWindow* _window, std::stack<State*>* _states) : window(_window), states(_states)
{
	this->quit = false;
	this->pause = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = 100.f;
}

State::~State()
{
}

//ACCESSORS
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

//UPDATES
void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 100.f * dt;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
		);
}


//FUNCTIONS
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->pause = true;
}

void State::unpauseState()
{
	this->pause = false;
}

