#include "render.h"
#include "transform.h"
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QDebug>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>

Render::Render(QImage* image)
    : texture(image) { }

void Render::draw(QPainter* painter, QPointF center, QRectF renderRect, float scale, float rotation)
{
    painter->save();

    painter->translate(center);
    painter->rotate(rotation);
    renderRect = QRectF(renderRect.topLeft()*scale, renderRect.bottomRight()*scale);

    painter->drawImage(renderRect, *texture);

    painter->restore();
}

const QColor green = QColor(0, 255, 0);
const QColor dimRed = QColor(255, 0, 0, 75);

void Render::drawWireframe(Transform* const transform, QPainter *painter)
{
    QPointF pos = transform->getPosition();
    QRectF colliderBounds = transform->getCollider()->getBounds();
    QRectF cRect = colliderBounds.adjusted(pos.x(), pos.y(), pos.x(), pos.y());

    // position
    painter->setPen(QPen(green));
    drawCircle(pos, 2, painter);

    // collider
    painter->setPen(QPen(dimRed));
    painter->drawRect(cRect);
}

void Render::drawCircle(QPointF center, float radius, QPainter *painter)
{
    QPointF delta(radius, radius);
    QRectF ellipseRect(center-delta, center+delta);
    QBrush oldBrush = painter->brush();
    painter->setBrush(QBrush(painter->pen().color()));
    painter->drawEllipse(ellipseRect);
    painter->setBrush(oldBrush);
}

QImage* Render::imageFromResource(QString resourcePath)
{
    QImage* fileImage = new QImage(resourcePath);
    fileImage->mirror(); // since we draw upside down for it to be geometrically familiar
    return fileImage;
}

QImage *Render::getTexture() const
{
    return texture;
}
