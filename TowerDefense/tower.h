#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>

class Tower : public QGraphicsItem
{
public:
    Tower(qreal x, qreal y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal m_radius;
    qreal m_towerSize;
};

#endif // TOWER_H
