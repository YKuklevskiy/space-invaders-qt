#ifndef GAMECONSTS_H
#define GAMECONSTS_H
#include <QPointF>
#include <QRectF>

///     Colliders    ///
const QRectF SPACESHIP_COLLIDER_R = QRectF(-25, -25, 50, 50);
const QRectF ALIEN_COLLIDER_R = QRectF(-30, -20, 60, 40);
const QRectF BOMB_COLLIDER_R = QRectF(-5, -15, 10, 30);
const QRectF ROCKET_COLLIDER_R = QRectF(-5, -15, 10, 30);
///     Colliders    ///



///      Aliens      ///
// individuals
const float BOMB_DROP_DELAY_MIN = 5;
const float BOMB_DROP_DELAY_MAX = 20;
const float ALIEN_SPEED = 45; // speed of alien cluster

// cluster
const int MAX_ALIEN_ROWS = 6; // how many aliens in one column max !DONT SET TO 1!
const int ALIEN_COLUMNS = 8; // how many aliens in one row !DONT SET TO 1!
const float ALIEN_DESCENT_DIST = 30;
const float WAVE_TIME = 3;
///      Aliens      ///



///     Spaceship    ///
const float SPACESHIP_SPEED = 550;
const float MAX_SPACESHIP_SWAY_DEG = 10;
const float SPACESHIP_ACCEL_MOD = 11.65f;
const float ROCKET_COOLDOWN = .4f;
const int INIT_LIFE_COUNT = 5;
const float REVIVE_TIME = 2.5f;
///     Spaceship    ///



///    Projectiles   ///
const float BOMB_VEL = 250;
const float ROCKET_VEL = 400;
///    Projectiles   ///



///       Field      ///
const float FIELD_BORDER = 50;
const QPointF SPACESHIP_INIT_POS = QPointF(150, FIELD_BORDER);
const float HORIZONTAL_ALIEN_OFFSET = 75; // initial free horizontal space
///       Field      ///

#endif // GAMECONSTS_H
