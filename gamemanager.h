#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "gameconsts.h"
#include "spaceship.h"
#include "textureholder.h"
#include "alienmanager.h"
#include "bomb.h"
#include "rocket.h"

class GameManager
{
public:
    GameManager(TextureHolder* const TH, QRectF windowRect);
    ~GameManager();

    void init(QRectF windowRect);

    void handleInputs(bool* input);
    void enumerate(float deltaTime, QRectF windowRect);
    void checkCollisions();

    void move();

    void render(QPainter* painter);

    int getLivesLeft() const;
    long getScore() const;

private:
    SpaceShip* spaceShip = nullptr;
    AlienManager* alienManager = nullptr;
    QList<Bomb*> bombs;
    QList<Rocket*> rockets;

    TextureHolder* TH;

    float rocketCurCD = 0.f;
    int livesLeft = INIT_LIFE_COUNT;
    float reviveTimer = REVIVE_TIME;

    long score = 0;

    void shootRocket();
    void throwBomb(AlienShip* thrower);

    bool objectOnScreen(QRectF windowRect, GameObject* const object);
    void handleRocketCollisions();
    void handleBombCollisions();

    void updateScore();
    void loseLife();
    void resetSpaceship();
    void handleRespawn(float deltaTime);
};

#endif // GAMEMANAGER_H
