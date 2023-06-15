#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#include "settings.h"
#include "game.h"
#include "menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids!");

    Menu menu(window);
    while (!menu.isGameStarted()) {
        menu.handleEvents();
        menu.update();
        menu.render();
    }


    // Start the game
    Game game(window);
    int score = game.run();
    cout << score;




    return 0;
}