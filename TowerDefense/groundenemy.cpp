#include "groundenemy.h"

extern Game *g;

GroundEnemy::GroundEnemy(QVector<QPoint> path, qreal speed, int maxHealth, int worth, QString pathToImg, QString pathToFlippedImg)
    : Enemy(speed, maxHealth, worth, pathToImg, EnemyType::GROUND_ENEMY), m_path(path)
    , m_pathToImage(pathToImg), m_pathToFlippedImage(pathToFlippedImg)
{
    // initial start and destination
    m_currentFromIndex = 0;
    m_currentDestIndex = 1;
    m_currentFrom = m_path[m_currentFromIndex];
    m_currentDest = m_path[m_currentDestIndex];

    setPos(m_currentFrom.x(), m_currentFrom.y());
}

void GroundEnemy::move()
{
    // if the xs are same, we move by y
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
            // enemy is moving from left to right
            m_currentImage = m_pathToImage;
            setPos(x() + m_speed, y());
        } else {
            // enemy is moving from right to left
            m_currentImage = m_pathToFlippedImage;
            setPos(x() - m_speed, y());
        }
    }

    // if we reached current destination, do the the next From/Dest
    if (int(x()) ==  m_currentDest.x() && int(y()) == m_currentDest.y()) {
//        qDebug() << "current destination reached";

        // if we reached the end, destroy the enemy
        if (m_currentDestIndex == (m_path.size()-1)) {
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
