#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector>
#include <QPoint>

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Enemy();

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void decreaseHealth(int amount);

private slots:
    void move();

private:
    qreal m_size;
    qreal m_healthBarDistance;

    qreal m_speed;
    qreal m_maxHealth;
    qreal m_currentHealth;

    QVector<QPoint> m_path;
    int m_currentFromIndex;
    int m_currentDestIndex;
    QPoint m_currentFrom;
    QPoint m_currentDest;
};

#endif // ENEMY_H
