#include "stdafx.h"
#include "Game.h"

//CONSTRUCTOR / DESTRUCTOR
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//INIT FUNCTIONS
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Survival Game");
	this->window->setFramerateLimit(120);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->states));
}

//UPDATE
void Game::updateDt()
{
	//updates dt variable with the time it takes to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application ends
	else
	{
		this->endApplication();
		this->window->close();
	}
}



void Game::render()
{
	this->window->clear();

	//render items
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
void Game::endApplication()
{
}
