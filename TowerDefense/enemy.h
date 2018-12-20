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

    QPointF getCurrentDestination() const;

private slots:
    void move();

private:
    qreal m_speed;
    qreal m_size;
    QVector<QPoint> m_path;
    int m_currentFromIndex;
    int m_currentDestIndex;
    QPoint m_currentFrom;
    QPoint m_currentDest;
};

#endif // ENEMY_H
