#ifndef ARROWTOWER_H
#define ARROWTOWER_H
#include "tower.h"

class ArrowTower: public Tower
{
    Q_OBJECT
public:
    ArrowTower(qreal x, qreal y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void fire();
public slots:
    void aquire_target();
};

#endif // ARROWTOWER_H
