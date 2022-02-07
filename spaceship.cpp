#include "spaceship.h"
#include <QDebug>
#include <QSize>

SpaceShip::SpaceShip(QPointF center, TextureHolder* TH)
    : GameObject()
{
    transform = new Transform(center, new Collider(SPACESHIP_COLLIDER_R));
    render = new Render(TH->getSpaceshipTexture());

    targetMasks.clear();
    targetMasks.append(BOMB);
    targetMasks.append(ALIENSHIP);
}

SpaceShip::~SpaceShip() { }

void SpaceShip::frameCalc(float deltaTime)
{
    SpaceShip::frameCalc(deltaTime, QSize(-1, -1));
}

void SpaceShip::frameCalc(float deltaTime, QSize windowSize)
{
    QPointF currentVelocity = transform->getVelocity().toPointF();
    QPointF targetVelocity = targetDirection.toPointF()*SPACESHIP_SPEED*deltaTime;
    float lerpMod = SPACESHIP_ACCEL_MOD*deltaTime;
    QVector2D estimatedVelocity = QVector2D(Transform::lerpPoint(currentVelocity, targetVelocity, lerpMod));

    if(windowSize.width() != -1) // check bordering ( костыль :( )
    {
        if(estimatedVelocity.x() < 0.0f)
        {
            float leftBorder = transform->getPosition().x()-transform->getCollider()->getBounds().width()*0.5f;
            float borderDiff = leftBorder + estimatedVelocity.x() - FIELD_BORDER;
            if (borderDiff < 0.0f)
                estimatedVelocity -= QVector2D(borderDiff, 0.0f);
        }
        else if(estimatedVelocity.x() > 0.0f)
        {
            float rightBorder = transform->getPosition().x()+transform->getCollider()->getBounds().width()*0.5f;
            float borderDiff = rightBorder + estimatedVelocity.x() + FIELD_BORDER-windowSize.width();
            if (borderDiff > 0.0f)
                estimatedVelocity -= QVector2D(borderDiff, 0.0f);
        }
    }

    // calculate rotation
    float rotationPercent = estimatedVelocity.x() / (SPACESHIP_SPEED*deltaTime);
    rotation = -rotationPercent * MAX_SPACESHIP_SWAY_DEG;

    transform->setVelocity(estimatedVelocity);
}

void SpaceShip::drawObject(QPainter *painter)
{
    // render->drawWireframe(transform, painter); // for development
    render->draw(painter, transform->getPosition(), transform->getCollider()->getBounds(), 1.0f, rotation);
}

void SpaceShip::moveObject()
{
    GameObject::moveObject();
}

void SpaceShip::setTargetDirection(const QVector2D &newTargetDirection)
{
    targetDirection = newTargetDirection;
}
