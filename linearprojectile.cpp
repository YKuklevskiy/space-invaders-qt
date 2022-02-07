#include "linearprojectile.h"

LinearProjectile::LinearProjectile(GameObject * const invoker, TextureHolder * const TH, float speed,
                                   QRectF colliderRect, QString invokeSide)
{
    short velo_modifier[2] = {0, 0};

    if(invokeSide == QString("bottom")) velo_modifier[1] = -1;
    else if(invokeSide == QString("left")) velo_modifier[0] = -1;
    else if(invokeSide == QString("right")) velo_modifier[0] = 1;
    else velo_modifier[1] = 1; // top

    QRectF invokerCollider = invoker->getTransform()->getWorldSpaceColliderRect();
    QPointF pos = invokerCollider.center();
    pos += QPointF(velo_modifier[0] * (invokerCollider.width() + colliderRect.width()) * 0.5f,
            velo_modifier[1] * (invokerCollider.height() + colliderRect.height()) * 0.5f);

    this->speed = QVector2D(velo_modifier[0]*speed, velo_modifier[1] * speed);

    transform = new Transform(pos, new Collider(colliderRect));
    render = new Render(TH->getSpaceshipTexture()); // default
}

void LinearProjectile::frameCalc(float deltaTime)
{
    QVector2D moveVec = speed * deltaTime;
    transform->setVelocity(moveVec);
}

void LinearProjectile::drawObject(QPainter *painter)
{
    GameObject::drawObject(painter);
}

void LinearProjectile::moveObject()
{
    GameObject::moveObject();
}
