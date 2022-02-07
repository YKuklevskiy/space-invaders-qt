#ifndef ALIENMANAGER_H
#define ALIENMANAGER_H
#include <QList>
#include <vector>
#include "alienship.h"
#include "textureholder.h"
#include "gameconsts.h"

class AlienManager
{
public:
    AlienManager(QRectF fieldRect);
    AlienManager(QRectF fieldRect, TextureHolder* TH);
    ~AlienManager();

    void init();

    void calcAliens(float deltaTime);
    void moveAliens();
    void deleteAlien(int column, int row);

    void drawField(QPainter* painter);

    const QRectF &getAlienFieldRect() const;

    const std::vector<QList<AlienShip *> > &getAlienVector() const;

private:
    QRectF windowRect; // rect of mainwindow
    TextureHolder* TH = nullptr;

    int curAlienRowCount = 1;
    float speedModifier = 1;
    enum AlienFieldState
    {
        FLYING_LEFT = 0,
        FLYING_DOWN_LEFT = 1,
        FLYING_RIGHT = 2,
        FLYING_DOWN_RIGHT = 3
    } currentState = AlienFieldState::FLYING_LEFT;

    float downDistanceLeft = 0.0f;
    float nextWaveTimer = WAVE_TIME;

    QRectF alienFieldRect;
    std::vector<QList<AlienShip*>> alienVector;

    void drawAliens(QPainter* painter);
    void drawBounds(QPainter* painter);

    int getAlienCount() const;
    void recalcRect();
    void recalcSpeedModifier();
    void handleRespawn(float deltaTime);
};

#endif // ALIENMANAGER_H
