//
// Created by Jakub Żywiecki on 08/05/2023.
//

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Spaceship : public Drawable, public Transformable {
private:
    ConvexShape shape;
    float dx=0, dy=0;
    float h_move = 0, v_move = 0;
public:
    Spaceship();
    ~Spaceship() = default;
    void moveShip(char move);
    void draw(RenderTarget& target, RenderStates states) const override;
    void updatePosition(float dt);

};


#endif //SPACESHIP_H
