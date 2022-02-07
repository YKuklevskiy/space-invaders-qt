#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H
#include <QImage>
#include "render.h"

class TextureHolder
{
public:
    TextureHolder();
    ~TextureHolder();

    void setTextures();

    QImage *getSpaceshipTexture() const;

    QImage *getRandomAlienTexture() const;

    QImage *getRocketTexture() const;

    QImage *getBombTexture() const;

    QImage *getBackgroundTexture() const;

private:
    QImage* spaceshipTexture = nullptr;
    QImage* alienshipTextures[2] = {nullptr, nullptr};
    QImage* rocketTexture = nullptr;
    QImage* bombTexture = nullptr;
    QImage* backgroundTexture = nullptr;
};

#endif // TEXTUREHOLDER_H
