#include "tower.h"

#include <QRectF>
#include <QPointF>
#include <QPainter>

#include <QtDebug>

Tower::Tower(qreal x, qreal y)
    : m_radius(100.0), m_xPos(x), m_yPos(y)
{
    // setPos(m_xPos, m_yPos);
}

QRectF Tower::boundingRect() const
{
    return QRectF(m_xPos - m_radius, m_yPos - m_radius, 2.0 * m_radius, 2.0 * m_radius);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPointF tower_center(m_xPos, m_yPos);

    // draw the radius of the tower
    painter->drawEllipse(tower_center, m_radius, m_radius);

    // draw the tower
    painter->setBrush(Qt::gray);
    painter->drawEllipse(tower_center, 30.0, 30.0);
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static int i = 0;
    qDebug() << "clicked" << i++;
}
