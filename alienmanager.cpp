#include "alienmanager.h"
#include <QDebug>

AlienManager::AlienManager(QRectF fieldRect) : windowRect(fieldRect)
{
    alienFieldRect = windowRect.adjusted(FIELD_BORDER+HORIZONTAL_ALIEN_OFFSET, windowRect.height()*0.5f, -FIELD_BORDER, -FIELD_BORDER);
}

AlienManager::AlienManager(QRectF fieldRect, TextureHolder *TH)
    : AlienManager(fieldRect)
{
    this->TH = TH;
    init();
}

AlienManager::~AlienManager()
{
    for(int i = 0; i < ALIEN_COLUMNS; i++)
        for(auto alien : alienVector[i])
            delete alien;
}

void AlienManager::init()
{
    alienFieldRect = windowRect.adjusted(FIELD_BORDER+HORIZONTAL_ALIEN_OFFSET, windowRect.height()*0.5f, -FIELD_BORDER, -FIELD_BORDER);

    // formula for alien[i][j] center:
    // we have alien center dxy = QSizeF(alien)*0.5f
    // every center of alien would be placed (fieldSize-centerDXY*2)/{widthCount, heightCount} apart
    // so dx = fieldSize.x() / widthCount, dy = fieldSize.y() / heightCount
    // and finally, alien[i][j] center = centerDXY + fieldSize/{widthCount-1, heightCount-1}*{i, j}

    QSizeF centerDXY2 = ALIEN_COLLIDER_R.size();

    float fieldDX = (alienFieldRect.width() - centerDXY2.width()) / (ALIEN_COLUMNS-1);
    float fieldDY = (alienFieldRect.height() - centerDXY2.height()) / (MAX_ALIEN_ROWS-1);

    alienVector.resize(ALIEN_COLUMNS);
    for (int row = 0; row < curAlienRowCount; row++) {
        for(int col = 0; col < ALIEN_COLUMNS; col++)
        {
            QPointF centerPoint(centerDXY2.width()*0.5f + fieldDX * col, -centerDXY2.height()*0.5f - fieldDY * row);
            centerPoint += QPointF(FIELD_BORDER + HORIZONTAL_ALIEN_OFFSET, windowRect.height() - FIELD_BORDER);

            alienVector[col].append(new AlienShip(centerPoint, TH));
        }
    }
}

void AlienManager::calcAliens(float deltaTime)
{
    handleRespawn(deltaTime);

    for (auto alienColumn : alienVector)
    {
        if(alienColumn.isEmpty()) continue;
        alienColumn.last()->calcBombs(deltaTime);
    }
    recalcRect();
    recalcSpeedModifier();

    // calc moveVector of rect
    QVector2D moveVector;
    if(currentState == FLYING_LEFT)
    {
        moveVector = QVector2D(-ALIEN_SPEED*deltaTime, 0);
        if(alienFieldRect.left() - ALIEN_SPEED*deltaTime < FIELD_BORDER)
        {
            currentState = FLYING_DOWN_LEFT;
            downDistanceLeft = ALIEN_DESCENT_DIST;
        }
    }
    else if(currentState == FLYING_RIGHT)
    {
        moveVector = QVector2D(ALIEN_SPEED*deltaTime, 0);
        if(alienFieldRect.right() + ALIEN_SPEED*deltaTime > windowRect.width() - FIELD_BORDER)
        {
            currentState = FLYING_DOWN_RIGHT;
            downDistanceLeft = ALIEN_DESCENT_DIST;
        }
    }
    else
    {
        moveVector = QVector2D(0, -ALIEN_SPEED*deltaTime*2);
        if(downDistanceLeft - moveVector.length() < 0.0f)
            currentState = (currentState == FLYING_DOWN_LEFT) ? FLYING_RIGHT : FLYING_LEFT;
        downDistanceLeft -= moveVector.length();
    }

    moveVector *= speedModifier; // speed up

    for (auto alienColumn : alienVector)
    {
        for(auto alien : alienColumn)
        {
            if(alien)
                alien->frameCalc(deltaTime, moveVector);
        }
    }
}

void AlienManager::moveAliens()
{
    for (auto alienColumn : alienVector)
    {
        for(auto alien : alienColumn)
        {
            if(alien)
                alien->moveObject();
        }
    }
}

void AlienManager::recalcRect()
{
    if(getAlienCount() == 0)
    {
        alienFieldRect = QRectF(0, 0, 0, 0);
        return;
    }
    float minX = windowRect.width() + 1, maxX = -1, minY = windowRect.height() + 1, maxY = -1;

    for(auto column : alienVector)
    {
        if(column.isEmpty()) continue;
        for(auto alien : column)
        {
            QRectF alienRect = alien->getTransform()->getWorldSpaceColliderRect();
            minX = (alienRect.left() < minX) ? alienRect.left() : minX;
            maxX = (alienRect.right() > maxX) ? alienRect.right() : maxX;
            minY = (alienRect.top() < minY) ? alienRect.top() : minY;
            maxY = (alienRect.bottom() > maxY) ? alienRect.bottom() : maxY;
        }
    }

    alienFieldRect = QRectF(minX, minY, (maxX-minX), (maxY-minY));
}

void AlienManager::deleteAlien(int column, int row)
{
    if(column < 0 || row < 0 || column > (int) alienVector.size() - 1) return;
    if(alienVector[column].size() - 1 < row) return;

    delete (alienVector[column].at(row));
    alienVector[column].erase(alienVector[column].begin() + row);
}

void AlienManager::drawField(QPainter *painter)
{
    drawAliens(painter);
    // drawBounds(painter); // for development
}

void AlienManager::drawAliens(QPainter *painter)
{
    for(auto col : alienVector)
        for(auto alien : col)
            alien->drawObject(painter);
}

const QColor red = QColor(255,0,0);

void AlienManager::drawBounds(QPainter *painter)
{
    painter->setPen(QPen(red));
    painter->drawRect(alienFieldRect);
}

const QRectF &AlienManager::getAlienFieldRect() const
{
    return alienFieldRect;
}

const std::vector<QList<AlienShip *> > &AlienManager::getAlienVector() const
{
    return alienVector;
}

int AlienManager::getAlienCount() const
{
    int alienCount = 0;
    for(auto column : alienVector)
    {
        if(column.isEmpty()) continue;
        for(auto alien : column)
            alienCount++;
    }
    return alienCount;
}

void AlienManager::recalcSpeedModifier()
{
    int alienCount = getAlienCount();
    float targetAlienCount = curAlienRowCount * ALIEN_COLUMNS;
    speedModifier = 1 + powf(1-alienCount/targetAlienCount, 2)*2; // 1 if all aliens alive, 3 if all dead
}

void AlienManager::handleRespawn(float deltaTime)
{
    if(getAlienCount() <= 0)
    {
        if(nextWaveTimer > 0)
            nextWaveTimer -= deltaTime;
        else
        {
            nextWaveTimer = WAVE_TIME;
            curAlienRowCount = std::min(curAlienRowCount + 1, MAX_ALIEN_ROWS); // increase row count
            init();
        }
    }
}
