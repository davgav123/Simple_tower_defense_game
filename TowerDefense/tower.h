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

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void fire();
    double distanceTo(QGraphicsItem * item);

public slots:
    void aquireTarget();

private:
    qreal m_radius;
    qreal m_towerSize;
    qreal m_towerCenterX;
    qreal m_towerCenterY;
    QPointF attackDest;
//    bool hasTarget;
//    QGraphicsItem *attackArea;
};

#endif // TOWER_H
