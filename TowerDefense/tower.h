#ifndef TOWER_H
#define TOWER_H

#include "enemy.h"
#include <QObject>
#include <QGraphicsItem>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Tower(qreal x, qreal y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int price() const;

    void fire();

public slots:
    void aquireTarget();

private:
    qreal m_radius;
    qreal m_towerSize;
    int m_damage;
    int m_price;

    Enemy * m_target;
};

#endif // TOWER_H
