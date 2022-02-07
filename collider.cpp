#include "collider.h"
#include "gameobject.h"
#include "transform.h"
#include <QDebug>

Collider::Collider(QRectF bounds)
    : bounds(bounds) { }

bool Collider::raycast(QVector2D ray, QPointF origin, QRectF target)
{
    if(target.contains(origin)) return true; // safe measures

    // more safe measures
    if(ray.x() == 0 && (origin.x() > target.right() || origin.x() < target.left()))
        return false;
    if(ray.y() == 0 && (origin.y() > target.top() || origin.y() < target.bottom()))
        return false;

    QPointF tNear = (target.topLeft()-origin);
    tNear.rx() /= ray.x();
    tNear.ry() /= ray.y();

    QPointF tFar = tNear;
    tFar.rx() += target.width()/ray.x();
    tFar.ry() += target.height()/ray.y();

    //sorting intersect coords by "nearness"
    if(tNear.x() > tFar.x())
    {
        float temp = tNear.x();
        tNear.rx() = tFar.x();
        tFar.rx() = temp;
    }
    if(tNear.y() > tFar.y())
    {
        float temp = tNear.y();
        tNear.ry() = tFar.y();
        tFar.ry() = temp;
    }

    if(tNear.x() > tFar.y() ||
       tNear.y() > tFar.x()) return false;

    float tHit = std::max(tNear.x(), tNear.y());
    // if(tHit >= 0.0f && tHit <= 1.0f) qDebug() << tHit;
    if(tHit < 0.0f || tHit > 1.0f) return false;

    return true;
}

bool Collider::checkObjectCollisionPF(GameObject* const object, GameObject* const target)
{
    if(!object || !target) return false;

    // ray origin
    QPointF originPos = object->getTransform()->getPosition();

    // ray vector, speed of origin relative to speed of target (to calculate moving object collisions)
    QVector2D originVelocity = object->getTransform()->getVelocity();
    QVector2D targetVelocity = target->getTransform()->getVelocity();
    QVector2D relativeVelocity = originVelocity - targetVelocity;

    if(relativeVelocity.length() == 0.0f) return false;

    // target (increased in size by half of origin size, to calculate collision in just one raycast)
    QRectF targetCollider = target->getTransform()->getWorldSpaceColliderRect();
    QRectF objectBounds = object->getTransform()->getCollider()->getBounds();
    QSizeF sizeHalved = QSizeF(objectBounds.width()*.5f, objectBounds.height()*.5f);
    targetCollider.adjust(-sizeHalved.width(), -sizeHalved.height(), sizeHalved.width(), sizeHalved.height());

    return raycast(relativeVelocity, originPos, targetCollider);
}

const QRectF &Collider::getBounds() const
{
    return bounds;
}

void Collider::setBounds(const QRectF &newBounds)
{
    bounds = newBounds;
}
