#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "InstructionsState.h"

class MainMenuState : public State
{
private:
    //Variables

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initFont();
    void initButtons();
public:
    MainMenuState(sf::RenderWindow*, std::stack<State*>* _states);
    virtual ~MainMenuState();

    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float&);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENUSTATE_H
