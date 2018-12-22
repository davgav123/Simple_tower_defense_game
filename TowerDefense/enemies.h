#ifndef GOBLIN_H
#define GOBLIN_H

#include "enemy.h"

class Goblin : public Enemy
{
public:
    Goblin(QVector<QPoint> path);
};

class CommonKnight : public Enemy
{
public:
    CommonKnight(QVector<QPoint> path);
};

class DarkKnight : public Enemy
{
public:
    DarkKnight(QVector<QPoint> path);
};


#endif // GOBLIN_H
