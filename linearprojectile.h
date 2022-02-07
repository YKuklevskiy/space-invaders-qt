#ifndef LINEARPROJECTILE_H
#define LINEARPROJECTILE_H

#include "gameobject.h"
#include "textureholder.h"

class LinearProjectile : public GameObject
{
public:
    LinearProjectile(GameObject* const invoker, TextureHolder* const TH, float speed, QRectF colliderRect,
                     QList<ObjectMask> targetMask = QList<ObjectMask>(DEFAULT),  QString invokeSide = "top");

    void frameCalc(float deltaTime) override;
    void drawObject(class QPainter* painter) override;
    void moveObject() override;

protected:
    QVector2D speed;

};

#endif // LINEARPROJECTILE_H
