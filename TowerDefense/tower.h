#ifndef TOWER_H
#define TOWER_H

#include "enemy.h"
#include <QObject>
#include <QGraphicsItem>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Tower(qreal x, qreal y, int damage, int price);

    QRectF boundingRect() const override;

    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override = 0;

    int price() const;

    virtual void fire();

public slots:
    void aquireTarget();
protected:
    Enemy * m_target;
    int m_damage;
    int m_price;
private:
    qreal m_radius;
    qreal m_towerSize;
};

#endif // TOWER_H
