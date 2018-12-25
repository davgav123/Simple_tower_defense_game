#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "enemy.h"

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy(qreal speed, int maxHealth, int worth, QString pathToImg);

private slots:
    void move();

private:
    // flying enemies should spawn in this radius at random positions at X axis
    int m_leftSpawnX;
    int m_rightSpawnX;
};

#endif // FLYINGENEMY_H
