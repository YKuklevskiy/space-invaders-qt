#include "gamemanager.h"
#include <QDebug>
#include <QApplication>

GameManager::GameManager(TextureHolder * const TH, QRectF windowRect)
    : TH(TH)
{
    init(windowRect);
}

GameManager::~GameManager()
{
    delete spaceShip;
    delete alienManager;
}

void GameManager::init(QRectF windowRect)
{
    if(spaceShip) return; // safe measures

    resetSpaceship();
    alienManager = new AlienManager(windowRect, TH);
}

void GameManager::enumerate(float deltaTime, QRectF windowRect)
{
    if(!spaceShip)
    {
        handleRespawn(deltaTime);
        return;
    }

    spaceShip->frameCalc(deltaTime, windowRect.size().toSize());
    alienManager->calcAliens(deltaTime);
    for(auto aliens : alienManager->getAlienVector())
    {
        if(aliens.isEmpty()) continue;
        aliens.last()->calcBombs(deltaTime);
        if(aliens.last()->getCurDropTime() < 0.0f)
        {
            throwBomb(aliens.last());
            aliens.last()->resetDropTimer();
        }
    }

    for(auto object : bombs)
        object->frameCalc(deltaTime);

    for(auto object : rockets)
        object->frameCalc(deltaTime);

    rocketCurCD -= deltaTime;

    // check screen visibility, clear outOfScreen objects
    for(int i = 0; i < rockets.length(); i++)
    {
        if(!objectOnScreen(windowRect, rockets.at(i)))
        {
            delete (rockets.at(i));
            rockets.erase(rockets.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < bombs.length(); i++)
    {
        if(!objectOnScreen(windowRect, bombs.at(i)))
        {
            delete (bombs.at(i));
            bombs.erase(bombs.begin() + i);
            i--;
        }
    }
}

bool GameManager::objectOnScreen(QRectF windowRect, GameObject* const object)
{
    QRectF objectRect = object->getTransform()->getWorldSpaceColliderRect();
    objectRect.translate(object->getTransform()->getVelocity().toPointF()); // next frame movement
    return windowRect.intersects(objectRect);
}

void GameManager::handleRocketCollisions()
{
    for(int i = 0; i < rockets.length(); i++)
    {
        // rocket-alien collision
        QRectF rocketRect = rockets.at(i)->getTransform()->getWorldSpaceColliderRect();
        if(rocketRect.intersects(alienManager->getAlienFieldRect())) // optimization
        {
            bool breakOuter = false;
            auto alienVec = alienManager->getAlienVector();
            for(int j = 0; j < (int) alienVec.size(); j++)
            {
                if(alienVec[j].isEmpty()) continue;
                for(int m = alienVec[j].size()-1; m >= 0; m--)
                {
                    if(Collider::checkObjectCollisionPF(rockets.at(i), alienVec[j][m]))
                    {
                        delete(rockets.at(i));
                        rockets.erase(rockets.begin()+i);
                        alienManager->deleteAlien(j, m);
                        updateScore();
                        i--;
                        breakOuter = true;
                        break;
                    }
                }
                if(breakOuter) break;
            }
            if(breakOuter) continue; // next rocket
        }

        //rocket-bomb collision
        for(int j = 0; j < bombs.length(); j++)
        {
            if(Collider::checkObjectCollisionPF(rockets.at(i), bombs.at(j)))
            {
                delete(rockets.at(i));
                rockets.erase(rockets.begin()+i);
                i--;
                break;
            }
        }
    }
}

void GameManager::handleBombCollisions()
{
    for(int i = 0; i < bombs.length(); i++)
    {
        if(Collider::checkObjectCollisionPF(spaceShip, bombs.at(i)))
        {
            loseLife();
            delete (bombs.at(i));
            bombs.erase(bombs.begin() + i);
            i--;
            break;
        }
    }
}

void GameManager::updateScore()
{
    score += 500;
}

void GameManager::loseLife()
{
    delete spaceShip;
    spaceShip = nullptr;
    livesLeft--;
}

void GameManager::resetSpaceship()
{
    spaceShip = new SpaceShip(SPACESHIP_INIT_POS, TH);
}

void GameManager::handleRespawn(float deltaTime)
{
    if(livesLeft <= 0) qApp->exit();

    if(reviveTimer > 0)
        reviveTimer -= deltaTime;
    else
    {
        reviveTimer = REVIVE_TIME;
        resetSpaceship();
    }
}

void GameManager::checkCollisions()
{
    if(!spaceShip) return;

    // check if alienFieldRect overlaps with spaceship, loss condition
    if(spaceShip->getTransform()->getWorldSpaceColliderRect().intersects(alienManager->getAlienFieldRect()))
    {
        livesLeft = 1; // hard-gameover
        loseLife();
    }

    // check rocket collisions with bombs and aliens
    handleRocketCollisions();

    // check bomb collisions with spaceship
    handleBombCollisions();
}

void GameManager::move()
{
    if(!spaceShip) return;

    spaceShip->moveObject();
    alienManager->moveAliens();

    for(auto object : bombs)
        object->moveObject();

    for(auto object : rockets)
        object->moveObject();
}

void GameManager::render(QPainter *painter)
{
    painter->drawImage(painter->window(), *TH->getBackgroundTexture());

    if(spaceShip)
        spaceShip->drawObject(painter);
    alienManager->drawField(painter);

    for(auto object : bombs)
        object->drawObject(painter);

    for(auto object : rockets)
        object->drawObject(painter);
}

void GameManager::handleInputs(bool* input)
{
    if(!spaceShip) return;

    if(input[0])
        spaceShip->setTargetDirection(QVector2D(-1, 0));
    if(input[1])
        spaceShip->setTargetDirection(QVector2D(1, 0));
    if(input[0]==input[1]) // not moving
        spaceShip->setTargetDirection(QVector2D(0, 0));
    if(input[2] && rocketCurCD < 0.0f)
    {
        rocketCurCD = ROCKET_COOLDOWN;
        shootRocket();
    }
}

int GameManager::getLivesLeft() const
{
    return livesLeft;
}

long GameManager::getScore() const
{
    return score;
}

void GameManager::shootRocket()
{
    rockets.append(new Rocket(spaceShip, TH));
}

void GameManager::throwBomb(AlienShip *thrower)
{
    bombs.append(new Bomb(thrower, TH));
}
