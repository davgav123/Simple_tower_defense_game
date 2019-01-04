#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"
#include "game.h"
#include <QTimer>
#include <QPainter>
#include <QRectF>
#include <QLineF>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <qmath.h>

class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(Enemy * e, qreal towerX, qreal towerY, int damage);

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
