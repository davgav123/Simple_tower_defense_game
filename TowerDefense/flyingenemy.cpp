#include "flyingenemy.h"
#include "game.h"

extern Game *g;

FlyingEnemy::FlyingEnemy(qreal speed, int maxHealth, int worth, QString pathToImg)
    : Enemy(speed, maxHealth, worth, pathToImg, EnemyType::FLYING_ENEMY)
    , m_leftSpawnX(400), m_rightSpawnX(1200)
{
    qsrand(unsigned(qrand()));
    // generate random X coord from spawn interval
    qreal initialX = m_leftSpawnX + (qrand() % (m_rightSpawnX - m_leftSpawnX));
    setPos(initialX, 0);
}

void FlyingEnemy::move()
{
    setPos(x(), y() + m_speed);

    //650 is the height of the map
    if (y() >= 650) {
        g->decreaseLives();
        destroyTheEnemy();
        return ;
    }
}
