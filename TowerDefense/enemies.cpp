// this file contains every enemy class

#include "enemies.h"

Goblin::Goblin(QVector<QPoint> path)
    : Enemy(path, 5.0, 100, 50, ":/images/goblin.png", ":/images/goblin_flipped.png")
{
}

CommonKnight::CommonKnight(QVector<QPoint> path)
    : Enemy(path, 5.0, 160, 80, ":/images/commonKnight.png", ":/images/commonKnightFlipped.png")
{
}

DarkKnight::DarkKnight(QVector<QPoint> path)
    : Enemy(path, 2.5, 250, 110, ":/images/darkKnight.png", ":/images/darkKnightFlipped.png")
{
}
