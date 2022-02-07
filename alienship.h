#ifndef ALIENSHIP_H
#define ALIENSHIP_H

#include "gameobject.h"
#include "textureholder.h"
#include "gameconsts.h"
#include <QVector2D>

class AlienShip : public GameObject
{
public:
    AlienShip(QPointF center, TextureHolder* TH);
    ~AlienShip();

    void frameCalc(float deltaTime) override;
    void frameCalc(float deltaTime, QVector2D moveVector);
    void drawObject(class QPainter* painter) override;

    void calcBombs(float deltaTime);
    void resetDropTimer();

    float getCurDropTime() const;

private:
    float curDropTime;
};

#endif // ALIENSHIP_H
