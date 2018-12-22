#include "watchtower.h"
#include "game.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>

extern Game *g;

WatchTower::WatchTower(qreal x, qreal y) : Tower(x, y, 20, 100)
{
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(aquireTarget()));
    timer->start(1000);
}

void WatchTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // draw the radius of the tower
    //painter->drawEllipse(tower_center, m_radius, m_radius);
    // draw the tower
    QPixmap pixmap(":/images/tower3.png");
    painter->drawPixmap(-25, -35, 50, 70, pixmap);
}

void WatchTower::fire()
{
    if (m_target == nullptr)
        return ;

    // shooting sounds
    qDebug() << "pew pew pew";

    // create bullet, and animate shooting
    Bullet *bullet = new Bullet(m_target, x(), y(), m_damage);

    QLineF ln(QPointF(x(), y()), m_target->pos());
    qreal angle = -1 * ln.angle();

    bullet->setRotation(angle);
    bullet->setPixmap(QPixmap(":/images/fireBall.jpg"));
    g->scene->addItem(bullet);
}

void WatchTower::aquire_target()
{
    Tower::aquireTarget();
}
