#ifndef MAGETOWER_H
#define MAGETOWER_H
#include "tower.h"

class MageTower: public Tower
{
    Q_OBJECT
public:
    MageTower(qreal x, qreal y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void fire();
public slots:
    void aquire_target();
};

#endif // MAGETOWER_H
