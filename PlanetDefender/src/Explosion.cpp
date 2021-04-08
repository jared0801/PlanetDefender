#include "Explosion.h"

Explosion::Explosion(sf::Texture* texture, float pos_x, float pos_y, float speed)
{
	this->originX = 0;
	this->originY = 0;
	this->explodeTimer = 0;
	this->explodeTimerMax = 10;
	this->speed = speed;
	this->initSprite(texture);

	this->sprite.setPosition(pos_x, pos_y);
}

Explosion::~Explosion()
{
}

void Explosion::update()
{
	this->sprite.move(0.f, this->speed);
	this->explodeTimer += 1;
	if (this->explodeTimer >= this->explodeTimerMax) {
		this->explodeTimer = 0;
		this->originX += 64;
		if (this->originX >= 256) {
			this->originX = 0;
			this->originY += 64;
			if (this->originY >= 256) {
				done = true;
			}
		}
		this->sprite.setTextureRect(sf::IntRect(this->originX, this->originY, 64, 64));
	}
}

void Explosion::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

bool Explosion::isDone() const
{
	return this->done;
}

void Explosion::initSprite(sf::Texture* texture)
{
	// Set the texture to the sprite
	this->sprite.setTexture(*texture);

	this->sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}