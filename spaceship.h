#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "gameobject.h"
#include <QVector2D>
#include "textureholder.h"
#include "gameconsts.h"

class SpaceShip : public GameObject
{
public:
    SpaceShip(QPointF center, TextureHolder* TH);
    ~SpaceShip();

    void frameCalc(float deltaTime) override;
    void frameCalc(float deltaTime, QSize windowSize);
    void drawObject(class QPainter* painter) override;
    void moveObject() override;

    void setTargetDirection(const QVector2D &newTargetDirection);

private:
    QVector2D targetDirection;
    float rotation = 0.f;
};

#endif // SPACESHIP_H
