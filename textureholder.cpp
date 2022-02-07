#include "textureholder.h"
#include <random>

TextureHolder::TextureHolder() { setTextures(); }

TextureHolder::~TextureHolder()
{
    delete spaceshipTexture;
    delete alienshipTextures[0];
    delete alienshipTextures[1];
    delete rocketTexture;
    delete bombTexture;
    delete backgroundTexture;
}

void TextureHolder::setTextures()
{
    QString resourcePath = QString(":/images/");
    spaceshipTexture = Render::imageFromResource(resourcePath + QString("spaceship.png"));
    alienshipTextures[0] = Render::imageFromResource(resourcePath + QString("alienship1.png"));
    alienshipTextures[1] = Render::imageFromResource(resourcePath + QString("alienship2.png"));
    rocketTexture = Render::imageFromResource(resourcePath + QString("rocket.png"));
    bombTexture = Render::imageFromResource(resourcePath + QString("bomb.png"));
    backgroundTexture = Render::imageFromResource(resourcePath + QString("bg.png"));
}

QImage *TextureHolder::getSpaceshipTexture() const
{
    return spaceshipTexture;
}

QImage *TextureHolder::getRandomAlienTexture() const
{
    return alienshipTextures[rand()%2];
}

QImage *TextureHolder::getRocketTexture() const
{
    return rocketTexture;
}

QImage *TextureHolder::getBombTexture() const
{
    return bombTexture;
}

QImage *TextureHolder::getBackgroundTexture() const
{
    return backgroundTexture;
}
