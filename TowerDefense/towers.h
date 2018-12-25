#ifndef ARROWTOWER_H
#define ARROWTOWER_H
#include "tower.h"

class WatchTower: public Tower
{
    Q_OBJECT
public:
    WatchTower(qreal x, qreal y);
};

class ArrowTower: public Tower
{
    Q_OBJECT
public:
    ArrowTower(qreal x, qreal y);
};

class IceTower: public Tower
{
    Q_OBJECT
public:
    IceTower(qreal x, qreal y);
};

class WitchTower: public Tower
{
    Q_OBJECT
public:
    WitchTower(qreal x, qreal y);
};

class MageTower: public Tower
{
    Q_OBJECT
public:
    MageTower(qreal x, qreal y);
};

#endif // ARROWTOWER_H
