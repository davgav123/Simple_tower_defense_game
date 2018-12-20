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
extern Enemy *enemy;

Tower::Tower(qreal x, qreal y)
    : QObject(), m_radius(100.0), m_towerCenterX(x), m_towerCenterY(y), m_towerSize(30.0)
{
     setPos(x, y);

     QTimer * timer = new QTimer();
     connect(timer, SIGNAL(timeout()),this, SLOT(aquireTarget()));
     timer->start(1000);
}

QRectF Tower::boundingRect() const
{
    // (0, 0) is the center of the tower
//    return QRectF(0 - m_towerSize, 0 - m_towerSize, 2.0 * m_towerSize, 2.0 * m_towerSize);
    return QRectF(0 - m_radius, 0 - m_radius, 2.0 * m_radius, 2.0 * m_radius);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // center of the item is (0, 0), or (400, 400) on the scene
    QPointF tower_center(0, 0);

    // draw the radius of the tower
    painter->drawEllipse(tower_center, m_radius, m_radius);

    // draw the tower
    QPixmap pixmap(":/images/tower.png");

    painter->drawPixmap(-25, -35, 50, 70, pixmap);
    qDebug()<<"File exists -"<<QFileInfo(":/images/tower.png").exists()<<" "<<QFileInfo(":/images/tower.png").absoluteFilePath();
//    painter->setBrush(Qt::gray);
//    painter->drawEllipse(tower_center, m_towerSize, m_towerSize);


//    painter->setBrush(Qt::green);
//    painter->drawEllipse(tower_center, m_towerSize * 2.0 / 3.0, m_towerSize * 2.0 / 3.0);

//    painter->setBrush(Qt::red);
//    painter->drawEllipse(tower_center, m_towerSize / 3.0, m_towerSize / 3.0);
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static int i = 0;
    qDebug() << "clicked" << i++;
    qDebug() << "x: " << event->pos().x() << " y:" << event->pos().y();
}

void Tower::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos() << "MOVE";

}

void Tower::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos() << "RELEASE";
    qDebug() << "x: " << event->pos().x() << " y:" << event->pos().y();
    Tower *t = new Tower(event->pos().x() + x(), event->pos().y() + y());
    g->scene->addItem(t);
}

void Tower::fire()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(m_towerCenterX, m_towerCenterY);

    QLineF ln(QPointF(m_towerCenterX, m_towerCenterY), attackDest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    g->scene->addItem(bullet);
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void Tower::aquireTarget()
{
    attackDest = enemy->getCurrentDestination();

    QLineF ln(pos(), attackDest);
    if (ln.length() < 2*m_radius) {
        fire();
    }
}











