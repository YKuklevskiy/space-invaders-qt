#include "gameui.h"

GameUI::GameUI(GameManager *GM, QRect windowRect)
    : GM(GM), windowRect(windowRect){ }

void GameUI::drawUI(QPainter *painter)
{
    painter->resetTransform();

    painter->setPen(QColor(255, 0, 0));

    drawLives(painter);
    drawScore(painter);
}

void GameUI::drawLives(QPainter* painter)
{
    QString lifeText = QString("Lives: ");
    lifeText.append(QString::fromStdString(std::to_string(GM->getLivesLeft())));

    QRect textBounds = painter->fontMetrics().boundingRect(lifeText);

    painter->drawText(UI_TEXT_BORDER, textBounds.height() + UI_TEXT_BORDER, lifeText);
}

void GameUI::drawScore(QPainter* painter)
{
    QString scoreText = QString("Score: ");
    scoreText.append(QString::fromStdString(std::to_string(GM->getScore())));

    QRect textBounds = painter->fontMetrics().boundingRect(scoreText);

    painter->drawText(windowRect.width()-textBounds.width() - UI_TEXT_BORDER, textBounds.height() + UI_TEXT_BORDER, scoreText);
}
