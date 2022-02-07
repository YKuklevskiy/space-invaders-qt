#include "alienship.h"

AlienShip::AlienShip(QPointF center, TextureHolder* TH)
{
    transform = new Transform(center, new Collider(ALIEN_COLLIDER_R));
    render = new Render(TH->getRandomAlienTexture());
    resetDropTimer();

    targetMasks.clear();
    targetMasks.append(ROCKET);
    targetMasks.append(SPACESHIP);
}

AlienShip::~AlienShip() { }

void AlienShip::frameCalc(float deltaTime)
{
    GameObject::frameCalc(deltaTime);
}

void AlienShip::frameCalc(float deltaTime, QVector2D moveVector)
{
    transform->setVelocity(moveVector);

    calcBombs(deltaTime);
}

void AlienShip::drawObject(QPainter *painter)
{
    GameObject::drawObject(painter);
}

void AlienShip::calcBombs(float deltaTime)
{
    curDropTime -= deltaTime;
}

void AlienShip::resetDropTimer()
{
    curDropTime = rand()%10000 * 0.0001f * (BOMB_DROP_DELAY_MAX-BOMB_DROP_DELAY_MIN) + BOMB_DROP_DELAY_MIN;
}

float AlienShip::getCurDropTime() const
{
    return curDropTime;
}
