#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#include <iostream>
#include "settings.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "SFML/Graphics.hpp"



int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Asteroids!");
    window.setFramerateLimit(60);
    Spaceship spaceship;
    vector<Bullet> bullets;
    vector<Asteroid> asteroids;
    int bulletCounter = 0;
    int asteroidsCounter = 0;
    int asteroidSpawnCounter = 0;
    int wait_bullet = 0;
    int wait_asteroids = 0;
    Clock clock;
    Event event;
    while (window.isOpen())
    {
        if (wait_asteroids == 0){
            Asteroid asteroid;
            asteroids.push_back(asteroid);
            asteroidsCounter += 1;
            wait_asteroids = 100;
        }
        if (wait_asteroids > 0){
            wait_asteroids -= 1;
        }

        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            spaceship.moveShip('u');
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            spaceship.moveShip('r');
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            spaceship.moveShip('l');
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)){
            if (wait_bullet == 0){
                Bullet bullet(spaceship.getPosition().x, spaceship.getPosition().y, spaceship.getRotation());
                bulletCounter += 1;
                bullets.push_back(bullet);
                wait_bullet = 50;
            }
        }
        if (wait_bullet > 0){
            wait_bullet -= 1;
        }
        window.clear();
        auto dt = clock.restart().asSeconds();
        spaceship.updatePosition(dt);

        auto start_bullets = bullets.begin();
        while (start_bullets != bullets.end()) {
            if (start_bullets->exists()) {
                start_bullets->updatePosition(dt);
                ++start_bullets;
            }
            else {
                start_bullets = bullets.erase(start_bullets);
                bulletCounter -= 1;
            }
        }

        auto start_asteroids = asteroids.begin();
        while (start_asteroids != asteroids.end()) {
            if (start_asteroids->exists()) {
                start_asteroids->updatePosition(dt);
                ++start_asteroids;
            }
            else {
                start_asteroids = asteroids.erase(start_asteroids);
                asteroidsCounter -= 1;
            }
        }
        window.draw(spaceship);
        for (int i = 0; i < bulletCounter; i++){
            window.draw(bullets.at(i));
        }
        for (int i = 0; i < asteroidsCounter; i++){
            window.draw(asteroids.at(i));
        }
        window.display();

    }
    return 0;
}

