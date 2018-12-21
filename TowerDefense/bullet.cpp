#include "bullet.h"

#include <QTimer>
#include <qmath.h>
#include <QPainter>
#include <QRectF>
#include <QLineF>

#include <QDebug>

Bullet::Bullet(Enemy * e, qreal towerX, qreal towerY, int damage)
    : m_size(5.0), m_target(std::move(e)), m_damage(damage)
{
    setPos(towerX, towerY);

    // init distances
    m_currentDist = INFINITY;
    m_previousDist = INFINITY;

    // create and start the timer
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-m_size * 4.0, -m_size, 8.0 * m_size, 2.0 * m_size);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(QPointF(0.0, 0.0), 4.0 * m_size, m_size);
}

void Bullet::move()
{
    int STEP_SIZE = 80;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    m_previousDist = m_currentDist;
    m_currentDist = QLineF(pos(), m_target->pos()).length();

    // if the distance is increasing, then bullet passed the enemy, so we delete the bullet
    if (m_previousDist < m_currentDist) {
        qDebug() << "destroying bullet";
        m_target->decreaseHealth(m_damage);
        delete this;
    }
}
