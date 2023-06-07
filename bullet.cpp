//
// Created by Jakub Żywiecki on 17/05/2023.
//

#include <cmath>
#include "bullet.h"
#include "settings.h"
Bullet::Bullet() {
    active = true;
}

Bullet::Bullet(float x, float y, float rotation) {
    float radius = 2.0f; // Radius of the bullet

    shape.setRadius(radius);
    shape.setFillColor(Color::White);
    shape.setPosition(x, y);
    shape.setRotation(rotation);

    active = true;
}

void Bullet::draw(RenderTarget& target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}

void Bullet::updatePosition(float dt) {
    float rotation = shape.getRotation();
    float x_speed = cos(rotation * 0.0174532925);
    float y_speed = sin(rotation * 0.0174532925);
    shape.move(x_speed * BULLET_SPEED * dt, y_speed * BULLET_SPEED * dt);
}

bool Bullet::exists() {
    Vector2f position = shape.getPosition();
    return position.x >= 0.0f && position.x <= WIDTH && position.y >= 0.0f && position.y <= HEIGHT;
}

CircleShape& Bullet::getShape() {
    return shape;
}

bool Bullet::isActive() const {
    return active;
}

void Bullet::setActive(bool active) {
    this->active = active;
}