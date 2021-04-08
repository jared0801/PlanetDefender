#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Explosion.h"
#include <sstream>
#include <map>

enum class GameState { START = 0, GAME, END };

class Game {
public:

	Game();
	~Game();


	// Functions
	void run();
	void update();
	void render();

private:
	// Window
	sf::RenderWindow* window;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// Player
	Player* player;
	int score = 0;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// Enemies
	std::vector<Asteroid*> enemies;
	std::vector<Explosion*> explosions;
	float spawnTimer;
	float spawnTimerMax;

	// GUI
	GameState gs;
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	// World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;

	// Private functions
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initGUI();
	void initWorld();


	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void updateExplosions();
	void updateCollision();
	void updateWorld();
	void updateGUI();


	void renderGUI();
	void renderWorld();

};