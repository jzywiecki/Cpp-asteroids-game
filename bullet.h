//
// Created by Jakub Żywiecki on 17/05/2023.
//

#ifndef FINAL_PROJECT_BULLET_H
#define FINAL_PROJECT_BULLET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet : public Drawable, public Transformable {
private:
    CircleShape shape;
    bool active;
public:
    Bullet();
    Bullet(float x, float y, float rotation);
    ~Bullet() = default;
    void draw(RenderTarget& target, RenderStates states) const override;
    void updatePosition(float dt);
    bool exists();
    CircleShape& getShape();
    bool isActive() const;
    void setActive(bool active);
};
#endif //FINAL_PROJECT_BULLET_H