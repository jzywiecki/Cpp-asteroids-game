#include "game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window)
    : window(window),
      spaceship(),
      bullets(),
      asteroids(),
      bulletCounter(0),
      asteroidsCounter(0),
      wait_bullet(0),
      wait_asteroids(0),
      score(0),
      bestScore(0),
      gameOver(false) {
    window.setFramerateLimit(60);
    clock.restart();
}

int Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
    return score;
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle button clicks
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
                handleButtonClick(worldPos);
            }
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

void Game::handleButtonClick(const sf::Vector2f& mousePos) {
    if (gameOver) {
        // Check if "Try Again" button is clicked
        if (tryAgainButton.getGlobalBounds().contains(mousePos)) {
            restartGame();
        }

        // Check if "Quit" button is clicked
        if (quitButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }
}

void Game::restartGame() {
    // Reset game variables
    spaceship.setCurrentLifes(3);
    bullets.clear();
    asteroids.clear();
    bulletCounter = 0;
    asteroidsCounter = 0;
    wait_bullet = 0;
    wait_asteroids = 0;
    score = 0;
    gameOver = false;
}

int Game::update() {
    if (wait_asteroids == 0 && !gameOver){
        Asteroid asteroid;
        while (asteroid.getShape().getGlobalBounds().intersects(spaceship.getShape().getGlobalBounds())){
            std::cout <<"You should consider playing the lottery today! c:\n";
            asteroid = Asteroid();
        }
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
            score += SCORE_FOR_ASTEROID;
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
                gameOver = true;
                if (score > bestScore) {
                    bestScore = score;
                }
            }
            asteroids[i].setActive(false);
            score -= SCORE_FOR_ASTEROID;
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

    score += SCORE_FOR_ASTEROID * (asteroidsCounter - asteroids.size());
    asteroidsCounter = asteroids.size();

    return score;
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

    // Display score
    sf::Font font;
    font.loadFromFile("../resources/ARCADECLASSIC.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Score " + std::to_string(score));
    text.setCharacterSize(60);
    text.setPosition(10, 10);
    window.draw(text);

    // Display best score if game is over
    if (gameOver) {
        bullets.clear();
        asteroids.clear();
        bulletCounter = 0;
        asteroidsCounter = 0;
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over!");
        gameOverText.setCharacterSize(80);
        gameOverText.setPosition(WIDTH / 2 - gameOverText.getGlobalBounds().width / 2, HEIGHT / 2 - gameOverText.getGlobalBounds().height / 2);
        window.draw(gameOverText);

        sf::Text bestScoreText;
        bestScoreText.setFont(font);
        bestScoreText.setString("Best Score " + std::to_string(bestScore));
        bestScoreText.setCharacterSize(40);
        bestScoreText.setPosition(WIDTH / 2 - bestScoreText.getGlobalBounds().width / 2, HEIGHT / 2 + 50);
        window.draw(bestScoreText);

        // Draw "Try Again" button
        tryAgainButton.setSize(sf::Vector2f(200, 50));
        tryAgainButton.setFillColor(sf::Color::Green);
        tryAgainButton.setPosition(WIDTH / 2 - tryAgainButton.getSize().x / 2, HEIGHT / 2 + 120);
        window.draw(tryAgainButton);

        sf::Text tryAgainText;
        tryAgainText.setFont(font);
        tryAgainText.setString("Try Again");
        tryAgainText.setCharacterSize(30);
        tryAgainText.setPosition(tryAgainButton.getPosition().x + tryAgainButton.getSize().x / 2 - tryAgainText.getGlobalBounds().width / 2,
                                  tryAgainButton.getPosition().y + tryAgainButton.getSize().y / 2 - tryAgainText.getGlobalBounds().height / 2);
        window.draw(tryAgainText);

        // Draw "Quit" button
        quitButton.setSize(sf::Vector2f(100, 50));
        quitButton.setFillColor(sf::Color::Red);
        quitButton.setPosition(WIDTH / 2 - quitButton.getSize().x / 2, HEIGHT / 2 + 190);
        window.draw(quitButton);

        sf::Text quitText;
        quitText.setFont(font);
        quitText.setString("Quit");
        quitText.setCharacterSize(30);
        quitText.setPosition(quitButton.getPosition().x + quitButton.getSize().x / 2 - quitText.getGlobalBounds().width / 2,
                             quitButton.getPosition().y + quitButton.getSize().y / 2 - quitText.getGlobalBounds().height / 2);
        window.draw(quitText);
    }

    window.display();
}