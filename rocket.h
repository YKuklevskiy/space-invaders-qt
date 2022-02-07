#ifndef ROCKET_H
#define ROCKET_H

#include "linearprojectile.h"
#include "spaceship.h"
#include "textureholder.h"
#include "gameconsts.h"

class Rocket : public LinearProjectile
{
public:
    Rocket(SpaceShip* const invoker, TextureHolder* const TH);

    void frameCalc(float deltaTime) override;
    void drawObject(class QPainter* painter) override;
    void moveObject() override;
};

#endif // ROCKET_H
