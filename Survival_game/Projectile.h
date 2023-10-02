#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once

#include "Entity.h"
#include "Enemy.h"

class Projectile : public Entity
{
private:
	std::shared_ptr<Enemy> target = nullptr;
public:
	Projectile(float x, float y, sf::Texture& texture_sheet, objectType);
	virtual ~Projectile();

	void setTarget(std::shared_ptr<Enemy>&);
	std::shared_ptr<Enemy> getTarget() const;
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);

	void findTarget(std::list<std::shared_ptr<Enemy>>&);
};

#endif // !PROJECTILE_H