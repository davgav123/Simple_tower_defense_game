#include "enemy.h"
#include "game.h"

#include <QRectF>
#include <QTimer>
#include <QPainter>
#include <QPointF>
#include <QtDebug>

extern Game *g;

Enemy::Enemy(QVector<QPoint> path)
    : m_path(path)
{
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

    // when you destroy the enemy, the gold increases by this amount
    m_worthInGold = 50;

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
    painter->drawRect(QRectF(-m_size, -m_size - m_healthBarDistance,
                             2.0 * m_size, 10.0));

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
        g->increaseScore(10);
        g->increaseGold(m_worthInGold);
        destroyTheEnemy();
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

    // if we reached current destination, do the the next From/Dest
    if ((int) x() ==  m_currentDest.x() && (int) y() == m_currentDest.y()) {
        qDebug() << "current destination reached";

        // if we reached the end, destroy the enemy
        if (m_currentDestIndex == (m_path.size()-1)) {
            qDebug() << "enemy reached the end of the path";

            // decrease the numberOfLives and delete the enemy
            g->decreaseLives();
            destroyTheEnemy();

             // without this return, the program crashes when the enemy reaches the end of the path
            return ;
        }

        m_currentFromIndex++;
        m_currentDestIndex++;
        m_currentFrom = m_path[m_currentFromIndex];
        m_currentDest = m_path[m_currentDestIndex];
    }
}

void Enemy::destroyTheEnemy()
{
    // remove the enemy from list of the enemies, and then delete it
    qDebug() << "enemy destroyed";
    g->removeEnemy(this);
    delete this;
}



















