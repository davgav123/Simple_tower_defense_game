#ifndef ICETOWER_H
#define ICETOWER_H
#include "tower.h"

class IceTower: public Tower
{
    Q_OBJECT
public:
    IceTower(qreal x, qreal y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void fire();
public slots:
    void aquire_target();
};

#endif // ICETOWER_H
