#ifndef BOMB_H
#define BOMB_H

#include "linearprojectile.h"
#include "alienship.h"
#include "textureholder.h"
#include "gameconsts.h"

class Bomb : public LinearProjectile
{
public:
    Bomb(AlienShip* const invoker, TextureHolder* const TH);

    void frameCalc(float deltaTime) override;
    void drawObject(class QPainter* painter) override;
    void moveObject() override;
};

#endif // BOMB_H
