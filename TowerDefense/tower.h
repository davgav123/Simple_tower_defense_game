#ifndef TOWER_H
#define TOWER_H

#include "enemy.h"
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <qmath.h>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Tower(qreal x, qreal y, int damage, int price, EnemyType type);

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

    // type of enemies that the tower can shoot
    EnemyType m_type;

    int m_damage;
    int m_price;
    QMediaPlayer *bulletSound;
private:
    qreal m_radius;
    qreal m_towerSize;

    void findClosestEnemy();
};

#endif // TOWER_H
