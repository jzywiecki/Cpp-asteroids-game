//
// Created by Jakub Żywiecki on 17/05/2023.
//

#include <cmath>
#include "bullet.h"
#include "settings.h"

Bullet::Bullet() {

}

Bullet::Bullet(float x, float y, float rotation) {
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(20.0f, 0.0f));
    shape.setPoint(1, sf::Vector2f(20.0f, 15.0f));
    shape.setPoint(2, sf::Vector2f(-20.0f, 15.0f));
    shape.setPoint(3, sf::Vector2f(-20.0f, 0.0f));

    shape.setFillColor(sf::Color(255, 255, 255, 1));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(0.0f, 0.0f);

    setPosition(x, y);
    setRotation(rotation);
}




void Bullet::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}

void Bullet::updatePosition(float dt) {
    float rotation = getRotation();
    float x_speed = cos(rotation * 0.0174532925);
    float y_speed = sin(rotation * 0.0174532925);
    this->move(x_speed*BULLET_SPEED, y_speed*BULLET_SPEED);
}


bool Bullet::exists() {
    Vector2f position = getPosition();
    if (position.x < -10.0f)
        return false;
    else if (position.x > WIDTH)
        return false;
    else if (position.y < -10.0f)
        return false;
    else if (position.y > HEIGHT)
        return false;
    return true;
}
