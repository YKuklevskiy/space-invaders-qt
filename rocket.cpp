#include "rocket.h"

Rocket::Rocket(SpaceShip * const invoker, TextureHolder * const TH)
    : LinearProjectile(invoker, TH, ROCKET_VEL, ROCKET_COLLIDER_R)
{
    delete render;
    render = new Render(TH->getRocketTexture());
}

void Rocket::frameCalc(float deltaTime)
{
    LinearProjectile::frameCalc(deltaTime);
}

void Rocket::drawObject(QPainter *painter)
{
    LinearProjectile::drawObject(painter);
}

void Rocket::moveObject()
{
    LinearProjectile::moveObject();
}
