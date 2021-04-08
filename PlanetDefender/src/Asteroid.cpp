#include "Asteroid.h"

Asteroid::Asteroid(float pos_x, float pos_y)
{

	this->originX = 0;
	this->originY = 0;
	this->rotateTimer = 0;
	this->rotateTimerMax = 50;
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(pos_x, pos_y);
}

Asteroid::~Asteroid()
{
}

void Asteroid::initVariables()
{

	difficulty = rand() % 10 + 3;
	hpMax = difficulty;
	hp = hpMax;
	damage = difficulty;
	points = difficulty;
	this->speed = static_cast<float>(difficulty / 3);
	switch ((int)speed) {
	case 1:
		this->rotateTimerMax = 10;
		break;
	case 2:
		this->rotateTimerMax = 30;
		break;
	case 3:
		this->rotateTimerMax = 50;
		break;
	}

	float scale = static_cast<float>(((double)rand() / RAND_MAX) / 2 + 0.5);
	sprite.setScale(sf::Vector2f(scale, scale));
}

void Asteroid::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("Assets/Textures/AsteroidAnimation.png")) {
		std::cout << "ERROR::Player::InitTexture::Could not load texture file.\n";
	}
}

void Asteroid::initSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	this->sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
}

void Asteroid::update()
{
	this->sprite.move(0.f, this->speed);
	this->rotateTimer += 1;

	if (this->rotateTimer >= this->rotateTimerMax) {
		this->rotateTimer = 0;
		this->originX += 128;
		if (this->originX >= 1024) {
			this->originX = 0;
			this->originY += 128;
			if (this->originY >= 1024) {
				this->originY = 0;
			}
		}
		this->sprite.setTextureRect(sf::IntRect(this->originX, this->originY, 128, 128));
	}
}

void Asteroid::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

sf::FloatRect Asteroid::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Asteroid::getDamage() const
{
	return this->damage;
}

int Asteroid::getPoints() const
{
	return this->points;
}

sf::Vector2f Asteroid::getPos() const
{
	return this->sprite.getPosition();
}

float Asteroid::getSpeed() const
{
	return this->speed;
}
