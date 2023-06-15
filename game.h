#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "settings.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"

class Game {
public:
    Game(sf::RenderWindow &window);

    int run();

private:
    sf::RenderWindow &window;
    Spaceship spaceship;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;
    int bulletCounter;
    int asteroidsCounter;
    int wait_bullet;
    int wait_asteroids;
    int lifes;
    sf::Clock clock;
    int score;
    bool gameOver;
    int bestScore;
    sf::RectangleShape tryAgainButton;
    sf::RectangleShape quitButton;

    void handleEvents();

    void handleButtonClick(const sf::Vector2f &mousePosition);

    void restartGame();

    int update();

    void render();
};

#endif // GAME_H