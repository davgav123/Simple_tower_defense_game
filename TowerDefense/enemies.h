#ifndef GOBLIN_H
#define GOBLIN_H

#include "groundenemy.h"
#include "flyingenemy.h"

class Goblin : public GroundEnemy
{
public:
    Goblin(QVector<QPoint> path);
};

class CommonKnight : public GroundEnemy
{
public:
    CommonKnight(QVector<QPoint> path);
};

class DarkKnight : public GroundEnemy
{
public:
    DarkKnight(QVector<QPoint> path);
};

class ZombieDino : public GroundEnemy
{
public:
    ZombieDino(QVector<QPoint> path);
};

class Rocket : public FlyingEnemy
{
public:
    Rocket();
};

#endif // GOBLIN_H
