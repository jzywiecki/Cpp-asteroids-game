//
// Created by Jakub Żywiecki on 08/05/2023.
//

#include <cmath>
#include "spaceship.h"
#include "settings.h"
#include <iostream>


Spaceship::Spaceship() {
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(20.0f, 0.0f));
    shape.setPoint(1, sf::Vector2f(-20.0f, 15.0f));
    shape.setPoint(2, sf::Vector2f(-20.0f, -15.0f));

    shape.setFillColor(sf::Color(255, 255, 255, 1));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setPosition(0.0f, 0.0f);

    setPosition(WIDTH/2, HEIGHT/2);
    setRotation(0.0f);
}


void Spaceship::updatePosition(float dt){
    if (h_move != 0){
        rotate(h_move* dt * ROTATION_SPEED);
        if (dx > 0){
            dx -= 0.01;
        }
        if (dy > 0){
            dy -= 0.01;
        }
        if (dy < 0){
            dy += 0.01;
        }
        if (dx < 0){
            dx += 0.01;
        }
    }
    if (v_move != 0){
        float rotation = getRotation();
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
    this->move(dx, dy);

    if (v_move > 0.0){
        v_move -= 0.01;
    }
    if (h_move > 0){
        h_move -= 0.1;
    }
    if (h_move < 0){
        h_move += 0.1;
    }
    if (h_move < 1e-05){
        h_move = 0;
    }
    if (h_move > 1e-05){
        h_move = 0;
    }
    Vector2f position = getPosition();
    if (position.x < -10.0f)
        position.x = WIDTH;
    else if (position.x > WIDTH)
        position.x = 0.0f;

    if (position.y < -10.0f)
        position.y = HEIGHT;
    else if (position.y > HEIGHT)
        position.y = 0.0f;
    setPosition(position);
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
}
