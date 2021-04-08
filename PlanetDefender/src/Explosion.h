#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Explosion
{
public:
	Explosion(sf::Texture* texture, float pos_x, float pos_y, float speed);
	~Explosion();

	void update();
	void render(sf::RenderTarget* target);

	//sf::FloatRect getBounds() const;

	bool isDone() const;

private:
	sf::Sprite sprite;

	// TODO: int type (?)
	int originX, originY;
	int explodeTimer, explodeTimerMax;
	bool done;
	float speed;

	void initSprite(sf::Texture* texture);
};

