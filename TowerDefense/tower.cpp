#include "tower.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsSceneMoveEvent>
#include <QFileInfo>
#include <QLineF>
#include <QtDebug>
#include <QTimer>
#include <QGraphicsItem>
#include <QList>

#include <QtDebug>

extern Game * g;

Tower::Tower(qreal x, qreal y)
    : m_radius(100.0), m_towerSize(30.0), m_damage(20)
{
     setPos(x, y);

     // initialy there is no target
     m_target = nullptr;

     QTimer * timer = new QTimer();
     connect(timer, SIGNAL(timeout()), this, SLOT(aquireTarget()));
     timer->start(1000);
}

QRectF Tower::boundingRect() const
{
    // (0, 0) is the center of the tower

    // this is just for the tower
//    return QRectF(0 - m_towerSize, 0 - m_towerSize, 2.0 * m_towerSize, 2.0 * m_towerSize);

    // this is for the tower with radius included
    return QRectF(0 - m_radius, 0 - m_radius, 2.0 * m_radius, 2.0 * m_radius);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // center of the item is (0, 0), or (400, 400) on the scene
    QPointF tower_center(0, 0);

    // draw the radius of the tower
    //painter->drawEllipse(tower_center, m_radius, m_radius);

    // draw the tower
    QPixmap pixmap(":/images/tower3.png");

    painter->drawPixmap(-25, -35, 50, 70, pixmap);
//    qDebug()<<"File exists -" << QFileInfo(":/images/tower.png").exists() << " "
//           << QFileInfo(":/images/tower.png").absoluteFilePath();

//    painter->setBrush();
//    painter->drawEllipse(tower_center, m_towerSize, m_towerSize);


//    painter->setBrush(Qt::green);
//    painter->drawEllipse(tower_center, m_towerSize * 2.0 / 3.0, m_towerSize * 2.0 / 3.0);

//    painter->setBrush(Qt::red);
//    painter->drawEllipse(tower_center, m_towerSize / 3.0, m_towerSize / 3.0);
}

void Tower::fire()
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
    g->scene->addItem(bullet);
}

void Tower::aquireTarget()
{
    // for every target find the closest enemy -> TODO

    // aquire target
    m_target = nullptr;
    if (! g->enemies().empty()) {
        m_target = std::move(g->enemies().takeFirst());

        // if the enemy is in range fire at it
        QLineF ln(pos(), m_target->pos());
        if (ln.length() < 1.5*m_radius && m_target != nullptr) {
            fire();
        }
    }
}











