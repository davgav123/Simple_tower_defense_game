#include "bullet.h"

extern Game *g;

Bullet::Bullet(Enemy * e, qreal towerX, qreal towerY, int damage)
    : m_size(3.0), m_damage(damage), m_target(std::move(e))
{
    m_targetPos = QPointF(m_target->x(), m_target->y());
    setPos(towerX, towerY);

    // init distances
    m_currentDist = double(INFINITY);
    m_previousDist = double(INFINITY);

    // create and start the timer
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    int STEP_SIZE = 50;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    m_previousDist = m_currentDist;
    m_currentDist = QLineF(pos(), m_targetPos).length();

    // if the distance is increasing, then bullet passed the enemy, so we delete the bullet
    if (m_previousDist <= m_currentDist) {

        // if enemy is not destroyed, we destroy it
        if (m_target != nullptr && g->containsEnemy(m_target)) {
            m_target->decreaseHealth(m_damage);
        }
        delete this;
    }
}
