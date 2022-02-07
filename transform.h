#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "collider.h"
#include <QPointF>
#include <QVector2D>

class Transform
{
public:
    Transform(QPointF position, Collider* collider);
    ~Transform();

    static QPointF lerpPoint(QPointF pointA, QPointF pointB, float t);

    void move();

    QPointF getPosition() const;

    Collider *getCollider() const;
    QRectF getWorldSpaceColliderRect();

    const QVector2D &getVelocity() const;

    void setVelocity(const QVector2D &newVelocity);

private:
    QPointF position;
    Collider* collider = nullptr;
    QVector2D velocity;
};

#endif // TRANSFORM_H
