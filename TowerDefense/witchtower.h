#ifndef WITCHTOWER_H
#define WITCHTOWER_H
#include "tower.h"

class WitchTower: public Tower
{
    Q_OBJECT
public:
    WitchTower(qreal x, qreal y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void fire();
public slots:
    void aquire_target();
};

#endif // WITCHTOWER_H
