#ifndef HITBOX_H
#define HITBOX_H	

#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite; //force sprite
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float widht, float height); //offset from position of sprite set on
	virtual ~HitboxComponent();

	const sf::FloatRect getRect();

	//Functions
	bool checkIntersect(const sf::FloatRect& fRect);
	

	void update();
	void render(sf::RenderTarget& target);
	
};

#endif // !HITBOX_H