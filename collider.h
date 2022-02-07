#ifndef COLLIDER_H
#define COLLIDER_H
#include <QRectF>
#include <QVector2D>
#include <QPointF>

class Collider
{
public:
    Collider(QRectF bounds);

    // casts a ray from origin to origin+ray, returns true if it intersects with target rectangle
    // written using info from javidx9's video on axis-aligned rectangle collisions https://youtu.be/8JJ-4JgR7Dg?t=1230
    static bool raycast(QVector2D ray, QPointF origin, QRectF target);

    // checks if during the following frame collider intersects with target's collider
    static bool checkObjectCollisionPF(class GameObject* const object, GameObject* const target);

    const QRectF &getBounds() const;
    void setBounds(const QRectF &newBounds);

private:
    QRectF bounds; // bounds of the collider relative to position of transform of gameobject
};

#endif // COLLIDER_H
