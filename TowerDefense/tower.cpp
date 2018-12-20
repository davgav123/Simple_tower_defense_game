#include "tower.h"

#include <QRectF>
#include <QPointF>
#include <QPainter>

#include <QtDebug>

Tower::Tower(qreal x, qreal y)
    : m_radius(100.0), m_towerSize(30.0)
{
     setPos(x, y);
}

QRectF Tower::boundingRect() const
{
    // (0, 0) is the center of the tower
//    return QRectF(0 - m_towerSize, 0 - m_towerSize, 2.0 * m_towerSize, 2.0 * m_towerSize);
    return QRectF(0 - m_radius, 0 - m_radius, 2.0 * m_radius, 2.0 * m_radius);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // center of the item is (0, 0), or (400, 400) on the scene
    QPointF tower_center(0, 0);

    // draw the radius of the tower
    painter->drawEllipse(tower_center, m_radius, m_radius);

    // draw the tower
    painter->setBrush(Qt::gray);
    painter->drawEllipse(tower_center, m_towerSize, m_towerSize);


    painter->setBrush(Qt::green);
    painter->drawEllipse(tower_center, m_towerSize * 2.0 / 3.0, m_towerSize * 2.0 / 3.0);

    painter->setBrush(Qt::red);
    painter->drawEllipse(tower_center, m_towerSize / 3.0, m_towerSize / 3.0);
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static int i = 0;
    qDebug() << "clicked" << i++;
    qDebug() << "x: " << x() << " y:" << y();
}


