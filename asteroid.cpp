//
// Created by Jakub Żywiecki on 17/05/2023.
//

#include <cmath>
#include "asteroid.h"
#include "settings.h"
#include <random>


Asteroid::Asteroid() {
    std::random_device rd;
    std::mt19937 rng(rd());
    int min1 = 0;
    int max1 = WIDTH;

    std::uniform_int_distribution<int> distribution1(min1, max1);
    int random_number1 = distribution1(rng);

    int min2 = 0;
    int max2 = HEIGHT;
    std::uniform_int_distribution<int> distribution2(min2, max2);
    int random_number2 = distribution2(rng);

    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(30.0f, 0.0f));
    shape.setPoint(1, sf::Vector2f(0.0f, 20.0f));
    shape.setPoint(2, sf::Vector2f(-20.0f, 0.0f));
    shape.setPoint(3, sf::Vector2f(0.0f, -20.0f));

    shape.setFillColor(sf::Color(255, 255, 255, 1));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(random_number1, random_number2);
    shape.setRotation(random_number1);
}

void Asteroid::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}

void Asteroid::updatePosition(float dt) {
    float rotation = shape.getRotation();
    float x_speed = cos(rotation * 0.0174532925);
    float y_speed = sin(rotation * 0.0174532925);
    shape.move(x_speed*ASTEROID_SPEED*dt, y_speed*ASTEROID_SPEED*dt);

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

bool Asteroid::isActive() {
    return active;
}

ConvexShape Asteroid::getShape() {
    return shape;
}

void Asteroid::setActive(bool active) {
    this->active = active;
}