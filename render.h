#ifndef RENDER_H
#define RENDER_H
#include <QPointF>
#include <QPainter>
#include <QImage>

class Render
{
public:
    Render(QImage* image);

    void draw(QPainter* painter, QPointF center, QRectF renderRect, float scale = 1.0f, float rotation = 0);
    void drawWireframe(class Transform* const transform, QPainter* painter);

    static void drawCircle(QPointF center, float radius, QPainter* painter);
    static QImage* imageFromResource(QString resourcePath); // fileName relative to .exe file folder

    QImage *getTexture() const;

private:
    QImage* texture = nullptr;
};

#endif // RENDER_H
