#include "enemy.h"
#include "game.h"

#include <QRectF>
#include <QTimer>
#include <QPainter>
#include <QPointF>

#include <QtDebug>

extern Game *g;

Enemy::Enemy()
{
    // create random path
    m_path << QPoint(300, 0) << QPoint(300, 700) << QPoint(600, 700)
           << QPoint(600, 400) << QPoint(1000, 400) << QPoint(1000, 900);

    // initial start and destination
    m_currentFromIndex = 0;
    m_currentDestIndex = 1;
    m_currentFrom = m_path[m_currentFromIndex];
    m_currentDest = m_path[m_currentDestIndex];

    // size and distance of the health bar from the center
    m_size = 30.0;
    m_healthBarDistance = 15.0;

    // speed and health
    m_speed = 5.0;
    m_maxHealth = 100.0;
    m_currentHealth = m_maxHealth;

    setPos(m_currentFrom.x(), m_currentFrom.y());

    // create and start the timer that moves the enemy
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

QRectF Enemy::boundingRect() const
{
    // rect needs to bound enemy and health bar
    return QRectF(-m_size, -m_size - m_healthBarDistance,
                  2.0 * m_size, 2.0 * m_size + m_healthBarDistance);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // draw the enemy
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(0, 0), m_size, m_size);

    // draw the health bar
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(-m_size, -m_size - m_healthBarDistance
                             , 2.0 * m_size, 10.0));

    // scale health from [0, 100] to [0, m_size*2]
    qreal currentHealthScaled = (m_currentHealth / m_maxHealth) * (2.0 * m_size);
    painter->setBrush(Qt::red);
    painter->drawRect(QRectF(-m_size, -m_size - m_healthBarDistance,
                             currentHealthScaled, 10.0));
}

void Enemy::decreaseHealth(int amount)
{
    m_currentHealth -= amount;

    // health is lower then zero (or equal) => enemy is dead
    if (m_currentHealth <= 0) {
        qDebug() << "enemy is deleted";
        g->score->increase();
        g->removeEnemy(this);
        delete this;
    }
}

void Enemy::move()
{
    // if  the xs are same, we move by y
    if (m_currentFrom.x() == m_currentDest.x()) {
        if (m_currentFrom.y() < m_currentDest.y()) {
            setPos(x(), y() + m_speed);
        } else {
            setPos(x(), y() - m_speed);
        }
    }

    // if the ys are same, we move by x
    if (m_currentFrom.y() == m_currentDest.y()) {
        if (m_currentFrom.x() < m_currentDest.x()) {
            setPos(x() + m_speed, y());
        } else {
            setPos(x() - m_speed, y());
        }
    }

//    qDebug() << m_currentFrom;
//    qDebug() << x() << " " << y();
//    qDebug() << m_currentDest;

    // if we reached current destination, do the the next From/Dest
    if ((int) x() ==  m_currentDest.x() && (int) y() == m_currentDest.y()) {
        qDebug() << "current destination reached";
//        qDebug() << m_currentFrom << " " << m_currentDest << " " << m_path.size();

        // if we reeached the end, destroy the enemy
        if (m_currentDestIndex == (m_path.size()-1)) {
            qDebug() << "enemy reached the end of the path";

            g->health->decrease();
            g->removeEnemy(this);
            delete this;
            return ;
        }

        m_currentFromIndex++;
        m_currentDestIndex++;
        m_currentFrom = m_path[m_currentFromIndex];
        m_currentDest = m_path[m_currentDestIndex];
    }
}



















