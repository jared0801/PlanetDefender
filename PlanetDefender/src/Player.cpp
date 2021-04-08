#include "Player.h"

void Player::initVariables()
{
	this->moveSpeed = 3.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("Assets/Textures/ship.png")) {
		std::cout << "ERROR::Player::InitTexture::Could not load texture file.\n";
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize the sprite
	this->sprite.scale(0.1f, 0.09f);
	//this->sprite.setOrigin(this->sprite.getTextureRect().width / 2.f, this->sprite.getTextureRect().height / 2.f);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

	this->sprite.setPosition(400, 500);
}

Player::~Player()
{

}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) this->hp = 0;
	//std::cout << hp << ", " << hpMax << std::endl;
}

void Player::update()
{
	this->updateAttack();
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
