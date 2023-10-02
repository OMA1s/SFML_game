#ifndef HELPER_H
#define HELPER_H

#pragma once
#include "stdafx.h"

//Function to get direction vector
sf::Vector2f getDirectionVector(sf::Vector2f point1, sf::Vector2f point2);

float distance(sf::Vector2f point1, sf::Vector2f point2);
#endif // !HELPER_H