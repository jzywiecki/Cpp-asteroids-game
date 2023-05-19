//
// Created by Jakub Żywiecki on 17/05/2023.
//

#ifndef FINAL_PROJECT_ASTEROID_H
#define FINAL_PROJECT_ASTEROID_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Asteroid : public Drawable, public Transformable{
private:
    ConvexShape shape;
    float dx=0, dy=0;
    float h_move = 0, v_move = 0;
public:
    Asteroid();
    ~Asteroid() = default;
    void draw(RenderTarget& target, RenderStates states) const override;
    void updatePosition(float dt);
    bool exists();
};


#endif //FINAL_PROJECT_ASTEROID_H
