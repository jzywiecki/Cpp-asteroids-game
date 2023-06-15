//
// Created by Jakub Żywiecki on 07/06/2023.
//

#ifndef FINAL_PROJECT_MENU_H
#define FINAL_PROJECT_MENU_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
public:
    Menu(sf::RenderWindow& window);

    void handleEvents();
    void update();
    void render();
    bool isGameStarted() const;
private:
    std::vector<CircleShape> dots;
    sf::RenderWindow& window;
    bool gameStarted;
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::RectangleShape startButton;
    sf::Text exitText;
    sf::RectangleShape exitButton;

};

#endif //FINAL_PROJECT_MENU_H
