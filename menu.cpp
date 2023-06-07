//
// Created by Jakub Żywiecki on 07/06/2023.
//

#include "menu.h"

Menu::Menu(sf::RenderWindow& window)
    : window(window),
      gameStarted(false) {
    if (!font.loadFromFile("../resources/Arial.ttf")) {
        // Handle font loading error
    }

    titleText.setFont(font);
    titleText.setString("Asteroids!");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(200.0f, 200.0f);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(300.0f, 300.0f);

    sf::FloatRect textBounds = startText.getGlobalBounds();
    startButton.setSize(sf::Vector2f(textBounds.width + 20.0f, textBounds.height + 10.0f));
    startButton.setPosition(textBounds.left - 10.0f, textBounds.top - 5.0f);
    startButton.setFillColor(sf::Color::Blue);
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

    window.display();
}

bool Menu::isGameStarted() const {
    return gameStarted;
}