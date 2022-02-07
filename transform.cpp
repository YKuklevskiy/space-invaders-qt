#include "transform.h"

Transform::Transform(QPointF position, Collider *collider)
    : position(position), collider(collider) { }

Transform::~Transform()
{
    delete collider;
}

QPointF Transform::lerpPoint(QPointF pointA, QPointF pointB, float t)
{
    return QPointF(pointA.x()+(pointB.x()-pointA.x())*t,
                   pointA.y()+(pointB.y()-pointA.y())*t);
}

void Transform::move()
{
    position += velocity.toPointF();
}

QPointF Transform::getPosition() const
{
    return position;
}

Collider *Transform::getCollider() const
{
    return collider;
}

QRectF Transform::getWorldSpaceColliderRect()
{
    return collider->getBounds().adjusted(position.x(), position.y(), position.x(), position.y());
}

const QVector2D &Transform::getVelocity() const
{
    return velocity;
}

void Transform::setVelocity(const QVector2D &newVelocity)
{
    velocity = newVelocity;
}
