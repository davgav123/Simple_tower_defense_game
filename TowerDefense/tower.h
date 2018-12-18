#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>

class Tower : public QGraphicsItem
{
public:
    Tower(qreal x = 0, qreal y = 0);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

private:
    qreal m_radius;
    qreal m_xPos;
    qreal m_yPos;
};

#endif // TOWER_H
