#include "stdafx.h"
#include "helperFuncs.h"
#include "GameState.h"

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initMap()
{
	//std::cout << "window x : " << this->window->getSize().x << "window y : " << this->window->getSize().y << std::endl;
	this->gameMap = new Map(this->window->getSize().x, this->window->getSize().y, this->textures["MAP"]);
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Assets/Sprites/Player/player_sheet.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	if (!this->textures["SKELETON_SHEET"].loadFromFile("Assets/Sprites/Enemy/skeleton_sheet.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SKELETON_TEXTURE!";
	if (!this->textures["GHOST_SHEET"].loadFromFile("Assets/Sprites/Enemy/ghost_sheet.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_GHOST_TEXTURE!";
	if (!this->textures["PROJECTILE"].loadFromFile("Assets/Sprites/Player/projectile.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PROJECTILE_TEXTURE!";
	if (!this->textures["MAP"].loadFromFile("Assets/Tiles/tileSheet.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAP_TEXTURE!";
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"], objectType::player);
}

void GameState::initEnemy()
{
	this->enemies.push_back(std::shared_ptr<Enemy>(new Enemy(800, 800, this->textures["SKELETON_SHEET"], objectType::skeleton)));
}

void GameState::initProjectile(Projectile* p)
{
	p->findTarget(this->enemies);
}

void GameState::initEndScreen()
{
	this->endGameScreen = new EndGameScreen(*this->window, this->font);

	this->endGameScreen->addButton("QUIT", 800.f, "Quit!");
}

void GameState::updateTime(const float& dt)
{
	//this->timeElapsed += dt;
	this->vectorRefresh += dt;
	
	if (this->vectorRefresh > 4.f)
	{
		this->garbageCollect();
		this->vectorRefresh = 0.f;
		this->createEnemy();
	}
}

void GameState::garbageCollect()
{
	//std::remove(this->projectiles.begin(), this->projectiles.end(), nullptr);
	this->projectiles.remove(nullptr);
	this->enemies.remove(nullptr);
}

//Constructor / Destructor
GameState::GameState(sf::RenderWindow* _window, std::stack<State*>* _states)
	: State(_window, _states)
{
	this->windowWidth = _window->getSize().x;
	this->windowHeight = _window->getSize().y;
	this->initFonts();
	this->initTextures();
	this->initEndScreen();
	this->initPlayers();
	this->initEnemy();
	this->initMap();
}

GameState::~GameState()
{
	for (auto &obj : enemies)
	{
		
		//delete obj;
		obj = nullptr;
	}
	delete this->player;
	this->player = nullptr;

	for (auto &pj : projectiles)
	{
		if (pj)
			delete pj;
		pj = nullptr;
	}
	delete this->gameMap;
	delete this->endGameScreen;
}

void GameState::createEnemy()
{
	this->enemies.push_back(std::shared_ptr<Enemy>(new Enemy(800, 800, this->textures["SKELETON_SHEET"], objectType::skeleton)));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeyTime())
	{
		this->endState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//this->checkForQuit();
	//get player position
	float x = this->player->getPosition().x;
	float y = this->player->getPosition().y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		if (this->player->canAttack())
		{
			this->player->updateAttack();
			this->createProjectile(x, y);
		}
	}
	//Player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (x > 0)
			this->player->move(-1.0f, 0.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (x < 1620)
			this->player->move(1.0f, 0.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (y > 0)
			this->player->move(0.0f, -1.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (y < 700)
			this->player->move(0.0f, 1.0f, dt);
	}
}

void GameState::updateEnemyInput(const float& dt)
{
	if (!this->player->getDead())
	{
		for (auto &obj : enemies)
		{
			if (obj)
			{
				if (obj->getDead())
				{
					//delete obj;
					obj = nullptr;
					continue;
				}
				if (obj->noLife())
					continue;
				if (obj->checkCollision(*this->player) && obj->canAttack())
				{
					obj->updateAttack();
					this->player->setDead(true);
					break;
				}

				sf::Vector2f dir = getDirectionVector(obj->getPosition(), player->getPosition());
				float x, y;
				if (dir.x > 0)
					x = 1;
				else
					x = -1;
				if (dir.y > 0)
					y = 1;
				else
					y = -1;
				obj->move(x, y, dt);
			}
			
		}
	}
	
	/*
	sf::Vector2f dir = getDirectionVector(enemy->getPosition(), player->getPosition());
	float x, y;
	if (dir.x > 0)
		x = 1;
	else
		x = -1;
	if (dir.y > 0)
		y = 1;
	else
		y = -1;
	this->enemy->move(x, y, dt);
	*/
}

void GameState::updateEndScreenButtons()
{
	if (this->endGameScreen->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::createProjectile(float x, float y)
{
	//int x = this->player->getPosition().x;
	//int y = this->player->getPosition().y;
	Projectile* p = new Projectile(y, x, this->textures["PROJECTILE"], objectType::inanimate);
	
	this->initProjectile(p);
	this->projectiles.push_back(p);
}

void GameState::deleteProjectile()
{
}

void GameState::updateProjectileInput(const float dt)
{
	for (auto &pj : projectiles)
	{
		if (pj)
		{
			
			//if projectile out of window, delete pj
			if (
				(pj->getPosition().x > (this->windowWidth)) || (pj->getPosition().x < -50)
				|| (pj->getPosition().y > (this->windowHeight)) || (pj->getPosition().y < -50)
				)
			{
				delete pj;
				pj = nullptr;
				continue;
			}
			
			if (pj->getTarget() && !pj->getTarget()->getDead())
			{
				//std::cout << pj->getTarget().use_count() << std::endl;
				sf::Vector2f dir = getDirectionVector(pj->getPosition(), pj->getTarget()->getPosition());
				float x, y;
				if (dir.x > 0)
					x = 1;
				else
					x = -1;
				if (dir.y > 0)
					y = 1;
				else
					y = -1;
				pj->move(x, y, dt);
			}
			else
			{
				if (this->enemies.empty())
					pj->move(this->player->getPosition().x, this->player->getPosition().y, dt);
				else
					pj->findTarget(this->enemies);
			}
			
			for (auto const &obj : enemies)
			{
				if (obj)
				{
					if (pj->checkCollision(*obj))
					{
						obj->takeHit();
						delete pj;
						pj = nullptr;
						break;
					}
				}
			}
		}
	}
}

void GameState::update(const float& dt)
{
	this->updateTime(dt);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	this->updateMousePositions();
	if (!this->player->getDead())
	{
		this->updatePlayerInput(dt);
	}
	else
	{
		this->endGameScreen->update(this->mousePosView);
		this->updateEndScreenButtons();
	}
	this->player->update(dt);
	this->updateEnemyInput(dt);

	this->updateProjectileInput(dt);

	
	for (auto const &obj : enemies)
	{
		if (obj)
			obj->update(dt);
	}

	for (auto const &pj : projectiles)
	{
		if (pj != nullptr)
			pj->update(dt);
	}
	//this->enemy->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	if (this->gameMap)
		this->gameMap->render(*target);
	if (this->player)
		this->player->render(*target);
	for (auto const &obj : enemies)
	{
		if (obj)
			obj->render(*target);
	}
	for (auto const &obj : projectiles)
	{
		if (obj)
			obj->render(*target);
	}
	if (this->player->getDead())
	{
		this->endGameScreen->render(*target);
	}
	
	//this->enemy->render(*target);
}