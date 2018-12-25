#include "towers.h"
#include "game.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QPixmap>

extern Game *g;

WatchTower::WatchTower(qreal x, qreal y)
    : Tower(x, y, 20, 100, EnemyType::GROUND_ENEMY, ":/images/tower3.png", "qrc:/sounds/bulletSound.mp3", ":/images/blackArrow.png")
{
}

ArrowTower::ArrowTower(qreal x, qreal y)
    : Tower(x, y, 35, 150, EnemyType::GROUND_ENEMY, ":/images/japaneseTowerForScene.png", "qrc:/sounds/bulletSound.mp3", ":images/arrow.png")
{
}

IceTower::IceTower(qreal x, qreal y)
    : Tower(x, y, 20, 120, EnemyType::FLYING_ENEMY, ":/images/iceTower.png", "qrc:/sounds/bulletSound.mp3", ":/images/iceTowerBullet.png")
{
}

WitchTower::WitchTower(qreal x, qreal y)
    : Tower(x, y, 35, 170, EnemyType::FLYING_ENEMY, ":/images/witch.png", "qrc:/sounds/bulletSound.mp3", ":/images/witchTowerBullet.png")
{
}

MageTower::MageTower(qreal x, qreal y)
    : Tower(x, y, 70, 350, EnemyType::BOTH_ENEMIES, ":/images/mageTower.png", "qrc:/sounds/bulletSound.mp3", ":/images/mageTowerBullet.png")
{
}

