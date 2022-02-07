#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "transform.h"
#include "collider.h"
#include "render.h"
#include "objectmask.h"
#include <QList>

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void frameCalc(float deltaTime); // performs all calculations and operations
    virtual void drawObject(class QPainter* painter); //well, you know
    virtual void moveObject(); // translates the object by its velocity vector

    Transform *getTransform() const;
    void setTransform(Transform *newTransform);

    Render *getRender() const;
    void setRender(Render *newRender);

protected:
    Transform* transform;
    Render* render;
    QList<ObjectMask> targetMasks;
};

#endif // GAMEOBJECT_H
