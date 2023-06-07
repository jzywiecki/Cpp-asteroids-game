#include "game.h"

Game::Game()
    : window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids!"),
      spaceship(),
      bullets(),
      asteroids(),
      bulletCounter(0),
      asteroidsCounter(0),
      wait_bullet(0),
      wait_asteroids(0) {
    window.setFramerateLimit(60);
    clock.restart();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        spaceship.moveShip('u');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        spaceship.moveShip('r');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        spaceship.moveShip('l');
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (wait_bullet == 0) {
            Bullet bullet(spaceship.getShape().getPosition().x, spaceship.getShape().getPosition().y, spaceship.getShape().getRotation());
            bulletCounter += 1;
            bullets.push_back(bullet);
            wait_bullet = BULLET_DELAY;
        }
    }
}

void Game::update() {
    if (wait_asteroids == 0) {
        Asteroid asteroid;
        asteroids.push_back(asteroid);
        asteroidsCounter += 1;
        wait_asteroids = 100;
    }
    if (wait_asteroids > 0) {
        wait_asteroids -= 1;
    }
    if (wait_bullet > 0) {
        wait_bullet -= 1;
    }

    auto dt = clock.restart().asSeconds();
    spaceship.updatePosition(dt);

    auto start_bullets = bullets.begin();
    while (start_bullets != bullets.end()) {
        if (start_bullets->exists()) {
            start_bullets->updatePosition(dt);
            ++start_bullets;
        } else {
            start_bullets = bullets.erase(start_bullets);
            bulletCounter -= 1;
        }
    }

    auto start_asteroids = asteroids.begin();
    while (start_asteroids != asteroids.end()) {
        if (start_asteroids->isActive()) {
            start_asteroids->updatePosition(dt);
            ++start_asteroids;
        } else {
            start_asteroids = asteroids.erase(start_asteroids);
            asteroidsCounter -= 1;
        }
    }

    // Detect collision between bullets and asteroids
    for (int i = 0; i < bulletCounter; i++) {
        for (int j = 0; j < asteroidsCounter; j++) {
            if (bullets.at(i).getShape().getGlobalBounds().intersects(asteroids.at(j).getShape().getGlobalBounds())) {
                bullets[i].setActive(false);
                asteroids[j].setActive(false);
            }
        }
    }

    for (int i = 0; i < asteroidsCounter; i++) {
        if (asteroids.at(i).getShape().getGlobalBounds().intersects(spaceship.getShape().getGlobalBounds())) {
            spaceship.setCurrentLifes(spaceship.getCurrentLifes() - 1);
            if (spaceship.getCurrentLifes() == 0) {
                std::cout << "Game over!" << std::endl;
                //todo  game over
            }
            asteroids[i].setActive(false);
        }
    }

    // Remove non-existing bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return !bullet.isActive();
        }),
        bullets.end()
    );
    bulletCounter = bullets.size();

    // Remove non-existing asteroids
    asteroids.erase(
        std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid asteroid) {
            return !asteroid.isActive();
        }),
        asteroids.end()
    );
    asteroidsCounter = asteroids.size();
}

void Game::render() {
    window.clear();

    window.draw(spaceship);
    for (int i = 0; i < bulletCounter; i++) {
        window.draw(bullets.at(i));
    }
    for (int i = 0; i < asteroidsCounter; i++) {
        window.draw(asteroids.at(i));
    }

    window.display();
}
