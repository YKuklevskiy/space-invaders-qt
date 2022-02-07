#include "gameobject.h"

GameObject::GameObject() { }

GameObject::~GameObject()
{
    delete transform;
    delete render;
}

void GameObject::frameCalc(float deltaTime)
{
    QVector2D moveVec = transform->getVelocity();
    moveVec *= deltaTime;
    transform->setVelocity(moveVec);
}

void GameObject::drawObject(QPainter *painter)
{
    // render->drawWireframe(transform, painter); // for development
    render->draw(painter, transform->getPosition(), transform->getCollider()->getBounds());
}

void GameObject::moveObject()
{
    transform->move();
}

Transform *GameObject::getTransform() const
{
    return transform;
}

void GameObject::setTransform(Transform *newTransform)
{
    transform = newTransform;
}

Render *GameObject::getRender() const
{
    return render;
}

void GameObject::setRender(Render *newRender)
{
    render = newRender;
}
