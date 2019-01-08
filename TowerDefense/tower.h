#ifndef TOWER_H
#define TOWER_H

#include "enemy.h"
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <qmath.h>
#include <QTimer>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Tower(qreal x, qreal y, int damage, int price, EnemyType type,
          QString pathToImg, QString pathToSound, QString pathToBulletImg);
    ~Tower() override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

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
    bool m_draw_radius = true;
    QGraphicsEllipseItem * ellipse;
    qreal m_radius;
    int m_towerSize;
    QString m_pathToImg;
    QString m_pathToBulletSound;
    QString m_pathToBulletImg;
    QTimer *m_timer;

    void findClosestEnemy();
};

#endif // TOWER_H
