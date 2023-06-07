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
    Game();
    void run();

private:
    sf::RenderWindow window;
    Spaceship spaceship;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;
    int bulletCounter;
    int asteroidsCounter;
    int wait_bullet;
    int wait_asteroids;
    int lifes;
    sf::Clock clock;

    void handleEvents();
    void update();
    void render();
};

#endif  // GAME_H