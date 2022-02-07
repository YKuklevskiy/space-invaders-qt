#ifndef GAMEUI_H
#define GAMEUI_H
#include "gamemanager.h"
#include <QPainter>

class GameUI
{
public:
    GameUI(GameManager* GM, QRect windowRect);

    void drawUI(QPainter* painter);

private:
    GameManager* GM;
    QRect windowRect;
    const int UI_TEXT_BORDER = 10; // border of text encased

    void drawLives(QPainter* painter);
    void drawScore(QPainter* painter);
};

#endif // GAMEUI_H
