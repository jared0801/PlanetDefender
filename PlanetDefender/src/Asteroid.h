#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Asteroid
{
public:
	Asteroid(float pos_x, float pos_y);
	~Asteroid();

	void update();
	void render(sf::RenderTarget* target);

	sf::FloatRect getBounds() const;
	const int& getDamage() const;

	int getPoints() const;

	sf::Vector2f getPos() const;

	float getSpeed() const;

private:
	sf::Sprite sprite;
	sf::Texture texture;
	int difficulty;
	int hp;
	int hpMax;
	int damage;
	int points;
	float scale;
	float speed;
	// TODO: int type (?)
	int originX, originY;
	int rotateTimer, rotateTimerMax;

	void initVariables();
	void initSprite();
	void initTexture();

};

