#ifndef WATCHTOWER_H
#define WATCHTOWER_H
#include "tower.h"

class WatchTower: public Tower
{
    Q_OBJECT
public:
    WatchTower(qreal x, qreal y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void fire();
public slots:
    void aquire_target();
};

#endif // WATCHTOWER_H
