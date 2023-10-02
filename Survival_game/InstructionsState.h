#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#pragma once

#include "State.h"
#include "Button.h"

class InstructionsState : public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    Button* backButton;

    //Instructions text variables
    sf::RectangleShape textBox;
    sf::Text instructionsMessage;

    void initInstructions();
    void initBackground();
    void initFont();
    void initButtons();
public:

    InstructionsState(sf::RenderWindow*, std::stack<State*>* _states);
    virtual ~InstructionsState();

    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float&);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !INSTRUCTIONS_H