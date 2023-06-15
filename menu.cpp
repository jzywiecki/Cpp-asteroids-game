//
// Created by Jakub Żywiecki on 07/06/2023.
//

#include "menu.h"
#include "settings.h"

Menu::Menu(sf::RenderWindow& window)
    : window(window),
      gameStarted(false) {
    if (!font.loadFromFile("../resources/ARCADECLASSIC.ttf")) {
        // Handle font loading error
    }

    titleText.setFont(font);
    titleText.setString("Asteroids");
    titleText.setCharacterSize(150);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(WIDTH / 2.0f - titleText.getGlobalBounds().width / 2.0f, 200.0f);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(100);
    startText.setPosition(WIDTH / 2.0f - startText.getGlobalBounds().width / 2.0f, 500.0f);

    sf::FloatRect textBounds = startText.getGlobalBounds();
    startButton.setSize(sf::Vector2f(textBounds.width + 20.0f, textBounds.height + 10.0f));
    startButton.setPosition(textBounds.left - 10.0f, textBounds.top - 5.0f);
    startButton.setFillColor(sf::Color::Black);

    exitText.setFont(font);
    exitText.setString("Exit Game");
    exitText.setCharacterSize(100);
    exitText.setPosition(WIDTH / 2.0f - exitText.getGlobalBounds().width / 2.0f, 700.0f);

    textBounds = exitText.getGlobalBounds();
    exitButton.setSize(sf::Vector2f(textBounds.width + 20.0f, textBounds.height + 10.0f));
    exitButton.setPosition(textBounds.left - 10.0f, textBounds.top - 5.0f);
    exitButton.setFillColor(sf::Color::Black);

    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        sf::CircleShape dot(3);
        dot.setPosition(rand() % WIDTH, rand() % HEIGHT);
        dot.setFillColor(sf::Color::White);
        dots.push_back(dot);
    }
}

void Menu::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (startButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                gameStarted = true;
            }
            if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                exit(0);
            }
        }
    }
}

void Menu::update() {
    // No update logic needed for the menu
}

void Menu::render() {
    window.clear();

    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
    window.draw(exitButton);
    window.draw(exitText);

    for (int i = 0; i < 20; i++) {
        if (dots[i].getPosition().x > WIDTH) {
            dots[i].setPosition(0, dots[i].getPosition().y);
        }
        if (dots[i].getPosition().y > HEIGHT) {
            dots[i].setPosition(dots[i].getPosition().x, 0);
        }

        dots[i].setPosition(dots[i].getPosition().x + 0.02, dots[i].getPosition().y + 0.02);
        window.draw(dots[i]);
    }

    window.display();
}

bool Menu::isGameStarted() const {
    return gameStarted;
}