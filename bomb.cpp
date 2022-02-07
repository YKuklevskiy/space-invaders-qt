#include "bomb.h"

Bomb::Bomb(AlienShip * const invoker, TextureHolder * const TH)
    : LinearProjectile(invoker, TH, BOMB_VEL, BOMB_COLLIDER_R, QList<ObjectMask>(), QString("bottom"))
{
    targetMasks.clear();
    targetMasks.append(ROCKET); targetMasks.append(SPACESHIP);

    delete render;
    render = new Render(TH->getBombTexture());
}

void Bomb::frameCalc(float deltaTime)
{
    LinearProjectile::frameCalc(deltaTime);
}

void Bomb::drawObject(QPainter *painter)
{
    LinearProjectile::drawObject(painter);
}

void Bomb::moveObject()
{
    LinearProjectile::moveObject();
}

