#include "Game.h"

// Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Planet Defender", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Assets/Textures/bullet.png");
	this->textures["EXPLOSION"] = new sf::Texture();
	this->textures["EXPLOSION"]->loadFromFile("Assets/Textures/explosion.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
	gs = GameState::START;

	// Load font
	if (!font.loadFromFile("Assets/Fonts/Dosis-Light.ttf")) {
		std::cout << "ERROR::GAME::Failed to load font!\n";
	}

	// Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Points: 0");
	this->pointText.setPosition(20.f, 50.f);

	// Init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
								   this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// Init player hp bar
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if (!worldBackgroundTex.loadFromFile("Assets/Textures/background1.jpg")) {
		std::cout << "ERROR::GAME::Could not load background texture.\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}


// Con / Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initGUI();
	this->initWorld();
}

Game::~Game() {
	delete this->window;
	delete this->player;

	for (auto& texture : this->textures) {
		delete texture.second;
	}

	for (auto* bullet : this->bullets) {
		delete bullet;
	}

	for (auto* asteroid : this->enemies) {
		delete asteroid;
	}
}

// Functions


void Game::run() {
	while (this->window->isOpen()) {
		this->updatePollEvents();

		this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed ||
			(e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape))
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	// Move player
	//player->update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);


	// Shoot
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		&& this->player->canAttack())
	{
		Bullet* left = new Bullet(this->textures["BULLET"],
								  this->player->getPos().x + this->player->getBounds().width / 2.f + 5,
								  this->player->getPos().y,
								  0.f, -1.f, 5.f);
		Bullet* right = new Bullet(this->textures["BULLET"],
								   this->player->getPos().x + this->player->getBounds().width / 2.f - 5,
								   this->player->getPos().y,
								   0.f, -1.f, 5.f);

		this->bullets.push_back(left);
		this->bullets.push_back(right);
	}
}

void Game::updateBullets()
{
	for (size_t i = 0; i < this->bullets.size(); i++) {
		bullets[i]->update();

		// Bullet culling (top of screen)
		if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0.f)
		{
			// Delete bullet
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
		}

	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Asteroid(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		bool asteroid_removed = false;
		enemies[i]->update();

		for (size_t k = 0; k < this->bullets.size() && !asteroid_removed; k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->score += this->enemies[i]->getPoints();

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				sf::Vector2f enemyCenter = sf::Vector2f(this->enemies[i]->getBounds().width / 4, this->enemies[i]->getBounds().height / 4);
				sf::Vector2f enemyPos = this->enemies[i]->getPos() + enemyCenter;
				float enemySpeed = this->enemies[i]->getSpeed();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				this->explosions.push_back(new Explosion(this->textures["EXPLOSION"], enemyPos.x, enemyPos.y, enemySpeed));

				asteroid_removed = true;
			}
		}

		if (!asteroid_removed) {
			if (enemies[i]->getBounds().top > this->window->getSize().y) {
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
			}
			// Asteroid player collision
			else if (enemies[i]->getBounds().intersects(this->player->getBounds()))
			{
				this->player->loseHp(this->enemies[i]->getDamage());
				sf::Vector2f enemyCenter = sf::Vector2f(this->enemies[i]->getBounds().width / 4, this->enemies[i]->getBounds().height / 4);
				sf::Vector2f enemyPos = this->enemies[i]->getPos() + enemyCenter;
				float enemySpeed = this->enemies[i]->getSpeed();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				this->explosions.push_back(new Explosion(this->textures["EXPLOSION"], enemyPos.x, enemyPos.y, enemySpeed));
			}
		}
	}
}


void Game::updateExplosions() {

	for (size_t i = 0; i < this->explosions.size(); i++) {
		this->explosions[i]->update();
		if (explosions[i]->isDone()) {
			delete this->explosions[i];
			this->explosions.erase(this->explosions.begin() + i);
		}
	}
}

void Game::updateCollision()
{
	// Left world boundary
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	// Right world boundary
	if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	// Bottom world boundary
	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateWorld()
{
	if (this->player->getHp() <= 0)
	{
		this->gs = GameState::END;
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->score;

	this->pointText.setString(ss.str());

	// Update player health bar
	//this->player->setHp(5);
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300 * hpPercent, this->playerHpBar.getSize().y));

}

void Game::update() {
	if (this->gs == GameState::START) {
		gs = GameState::GAME;
	}
	else if (this->gs == GameState::GAME) {
		this->updateInput();
		this->player->update();
		this->updateWorld();
		this->updateCollision();
		this->updateBullets();
		this->updateEnemies();
		this->updateExplosions();
		this->updateGUI();
	}
	else if (this->gs == GameState::END) {

	}
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render() {
	this->window->clear();

	// Draw stuff
	if (gs == GameState::START) {

	}
	else if (this->gs == GameState::GAME) {

		renderWorld();

		player->render(this->window);

		for (auto* bullet : this->bullets) {
			bullet->render(this->window);
		}

		for (auto* asteroid : this->enemies) {
			asteroid->render(this->window);
		}

		for (auto* explosion : this->explosions) {
			explosion->render(this->window);
		}

		renderGUI();

		if (this->player->getHp() <= 0) {
			this->window->draw(this->gameOverText);
		}
	}
	else if (gs == GameState::END) {

	}

	this->window->display();
}