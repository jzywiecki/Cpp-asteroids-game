//
// Created by Jakub Żywiecki on 08/05/2023.
//

#include <cmath>
#include "spaceship.h"
#include "settings.h"

Spaceship::Spaceship() {
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(20.0f, 0.0f));
    shape.setPoint(1, sf::Vector2f(-20.0f, 15.0f));
    shape.setPoint(2, sf::Vector2f(-20.0f, -15.0f));

    shape.setFillColor(sf::Color(255, 255, 255, 1));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setPosition(WIDTH/2, HEIGHT/2);
    shape.setRotation(0.0f);
}


void Spaceship::updatePosition(float dt){

    if (h_move != 0){ //obracanie
        shape.rotate(h_move * dt * ROTATION_SPEED);
        if (dx > 1e-05){
            dx -= 0.01;
        }
        if (dy > 1e-05){
            dy -= 0.01;
        }
        if (dy < 1e-05){
            dy += 0.01;
        }
        if (dx < 1e-05){
            dx += 0.01;
        }
    }
    if (v_move != 0){ //przyspieszanie
        float rotation = shape.getRotation();
        float x_speed = cos(rotation * 0.0174532925);
        float y_speed = sin(rotation * 0.0174532925);
        dx = v_move * ACCELERATION * dt * x_speed;
        dy = v_move * ACCELERATION * dt * y_speed;
        if (dx * dx > MAX_SPEED * MAX_SPEED){
            dx = dx > 0 ? MAX_SPEED : -MAX_SPEED;
        }
        if (dy * dy > MAX_SPEED * MAX_SPEED){
            dy = dy > 0 ? MAX_SPEED : -MAX_SPEED;
        }
    }

    //przesuwanie
    shape.move(SPACESHIP_SPEED* dx * dt, SPACESHIP_SPEED*dy * dt);

    //spowalnianie
    if (v_move > 1e-05){
        v_move -= 0.01;
    }
    if (h_move > 1e-05){
        h_move -= 0.03;
    }
    if (h_move < 1e-05){
        h_move += 0.03;
    }
    if (h_move < 1e-05 && h_move > -1e-05){
        h_move = 0;
    }
    if (h_move > 1e-05 && h_move < -1e-05){
        h_move = 0;
    }


    //zawijanie na mapie
    Vector2f position = shape.getPosition();
    if (position.x < -10.0f)
        position.x = WIDTH;
    else if (position.x > WIDTH)
        position.x = 0.0f;

    if (position.y < -10.0f)
        position.y = HEIGHT;
    else if (position.y > HEIGHT)
        position.y = 0.0f;
    shape.setPosition(position);
}


void Spaceship::moveShip(char move) {
    h_move = 0;
    v_move = 0;
    switch (move) {
        case 'u': {v_move = 1; break;}
        case 'l': {h_move = -1; break;}
        case 'r': {h_move = 1; break;}
    }
}

void Spaceship::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);

    // Draw life bar
    sf::RectangleShape lifeBar(sf::Vector2f(currentLifes * 30.0f, 10.0f));
    lifeBar.setPosition(shape.getPosition().x - 50.0f, shape.getPosition().y + 40.0f);
    lifeBar.setFillColor(sf::Color::Green);
    if (currentLifes <= 2){
        lifeBar.setFillColor(sf::Color::Yellow);
    }
    if (currentLifes <= 1){
        lifeBar.setFillColor(sf::Color::Red);
    }
    target.draw(lifeBar, states);
}

ConvexShape Spaceship::getShape(){
    return shape;
}

void Spaceship::setCurrentLifes(int lifes) {
    currentLifes = lifes;
}

int Spaceship::getCurrentLifes() const {
    return currentLifes;
}