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
    Tower(qreal x, qreal y, int damage, int price, EnemyType type,
          QString pathToImg, QString pathToSound, QString pathToBulletImg);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int price() const;
    int towerSize() const;

    void fire();

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
    int m_towerSize;

    QString m_pathToImg;
    QString m_pathToBulletSound;
    QString m_pathToBulletImg;

    void findClosestEnemy();
};

#endif // TOWER_H
