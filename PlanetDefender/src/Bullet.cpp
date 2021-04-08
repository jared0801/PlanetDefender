#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float move_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.3f, 0.3f);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->moveSpeed = move_speed;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	// Movement
	this->shape.move(this->moveSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}
