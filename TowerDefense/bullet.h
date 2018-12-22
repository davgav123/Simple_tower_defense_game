#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(Enemy * e, qreal towerX, qreal towerY, int damage);

//    QRectF boundingRect() const override;

//    void paint(QPainter *painter,
//               const QStyleOptionGraphicsItem *option,
//               QWidget *widget) override;

private slots:
    void move();

private:
    qreal m_size;
    int m_damage;
    Enemy * m_target;
    QPointF m_targetPos;

    qreal m_previousDist;
    qreal m_currentDist;

};

#endif // BULLET_H
