//
// Created by Jakub Żywiecki on 17/05/2023.
//

#ifndef FINAL_PROJECT_ASTEROID_H
#define FINAL_PROJECT_ASTEROID_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Asteroid : public Drawable, public Transformable{
private:
    float dx=0, dy=0;
    float h_move = 0, v_move = 0;
    bool active = true;
    float speed;
public:
    ConvexShape shape;
    Asteroid();
    ~Asteroid() = default;
    void draw(RenderTarget& target, RenderStates states) const override;
    void updatePosition(float dt);
    bool isActive();
    ConvexShape getShape();
    void setActive(bool active);
};


#endif //FINAL_PROJECT_ASTEROID_H
