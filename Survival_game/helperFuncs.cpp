#include "helperFuncs.h"

//Function to get direction vector
sf::Vector2f getDirectionVector(sf::Vector2f point1, sf::Vector2f point2)
{
	sf::Vector2f dir;
	dir.x = point2.x - point1.x;
	dir.y = point2.y - point1.y;
	return dir;
}
float distance(sf::Vector2f point1, sf::Vector2f point2)
{
	return (
		(point2.x - point1.x) * (point2.x - point1.x)
		)
		+
		(
			(point2.y - point1.y) * (point2.y - point1.y)
			)
		;
}
