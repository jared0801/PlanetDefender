#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
public:
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float move_speed);
	~Bullet();

	void update();
	void render(sf::RenderTarget* target);

	// Accessors
	const sf::FloatRect getBounds() const;
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float moveSpeed;
};