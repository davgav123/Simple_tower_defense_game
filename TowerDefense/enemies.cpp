// this file contains every enemy class

#include "enemies.h"

Goblin::Goblin(QVector<QPoint> path)
    : GroundEnemy(path, 5.0, 100, 30,
                  ":/images/goblin.png", ":/images/goblin_flipped.png")
{
}

CommonKnight::CommonKnight(QVector<QPoint> path)
    : GroundEnemy(path, 5.0, 160, 50,
                  ":/images/commonKnight.png", ":/images/commonKnightFlipped.png")
{
}

DarkKnight::DarkKnight(QVector<QPoint> path)
    : GroundEnemy(path, 2.5, 350, 80,
            ":/images/darkKnight.png", ":/images/darkKnightFlipped.png")
{
}

ZombieDino::ZombieDino(QVector<QPoint> path)
    : GroundEnemy(path, 2.5, 1000, 260, ":/images/zombieDinosaur.png", ":/images/zombieDinosaurFlipped.png")
{
}

Rocket::Rocket()
    : FlyingEnemy(2, 120, 40, ":/images/rocket.png")
{
}

Dragon::Dragon()
    : FlyingEnemy(2, 200, 60, ":/images/dragon.png")
{
}

ZombieDragon::ZombieDragon()
    : FlyingEnemy(2, 360, 90, ":/images/zombieDragon.png")
{

}
