#include "enemy.h"
#include "game.h"

#include <QRectF>
#include <QPainter>
#include <QPointF>
#include <QPixmap>

extern Game *g;

Enemy::Enemy(qreal speed, qreal maxHealth, int worth, QString currentImage, EnemyType type)
    : m_speed(speed), m_maxHealth(maxHealth), m_worthInGold(worth), m_currentImage(currentImage), m_type(type)
{
    // size and distance of the health bar from the center
    m_size = 20.0;
    m_healthBarDistance = 15.0;

    // health
    m_currentHealth = m_maxHealth;

    // create and start the timer that moves the enemy
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(move()));
    m_timer->start(50);
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
//    painter->drawEllipse(QPointF(0, 0), m_size, m_size); // <---- inser IMG
    painter->drawPixmap(int(-m_size), int(-m_size), int(2*m_size), int(2*m_size),
                        QPixmap(m_currentImage));

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

void Enemy::setMaxHealth(int newValue)
{
    m_maxHealth = newValue;
    m_currentHealth = m_maxHealth;
}

qreal Enemy::maxHealth() const
{
    return m_maxHealth;
}

void Enemy::destroyTheEnemy()
{
    // remove the enemy from list of the enemies, and then delete it
    g->scene->removeItem(this);
    g->removeEnemy(this);
    delete this;
}

EnemyType Enemy::enemyType() const
{
    return m_type;
}

Enemy::~Enemy()
{
    delete m_timer;
}



















