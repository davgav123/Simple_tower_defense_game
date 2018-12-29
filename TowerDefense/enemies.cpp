// this file contains every enemy class

#include "enemies.h"

Goblin::Goblin(QVector<QPoint> path)
    : GroundEnemy(path, 5.0, 110, 30,
                  ":/images/goblin.png", ":/images/goblin_flipped.png")
{
}

CommonKnight::CommonKnight(QVector<QPoint> path)
    : GroundEnemy(path, 5.0, 180, 40,
                  ":/images/commonKnight.png", ":/images/commonKnightFlipped.png")
{
}

DarkKnight::DarkKnight(QVector<QPoint> path)
    : GroundEnemy(path, 2.5, 410, 80,
            ":/images/darkKnight.png", ":/images/darkKnightFlipped.png")
{
}

ZombieDino::ZombieDino(QVector<QPoint> path)
    : GroundEnemy(path, 2.5, 1300, 190, ":/images/zombieDinosaur.png", ":/images/zombieDinosaurFlipped.png")
{
}

Moth::Moth()
    : FlyingEnemy(2, 140, 40, ":/images/moth.png")
{
}

Dragon::Dragon()
    : FlyingEnemy(2, 220, 60, ":/images/dragon.png")
{
}

ZombieDragon::ZombieDragon()
    : FlyingEnemy(2, 400, 90, ":/images/zombieDragon.png")
{

}
