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
#include <QGraphicsItem>
#include <QtDebug>
#include <QLinkedList>
#include <QGraphicsEllipseItem>

extern Game * g;

Tower::Tower(qreal x, qreal y, int damage, int price, EnemyType type, QString pathToImg, QString pathToSound, QString pathToBulletImg)
    : m_type(type), m_damage(damage), m_price(price), m_radius(100.0)
    , m_towerSize(60), m_pathToImg(pathToImg), m_pathToBulletSound(pathToSound), m_pathToBulletImg(pathToBulletImg)
{
    setPos(x,y);
    // initialy there is no target
    m_target = nullptr;
    setAcceptHoverEvents(true);

    // timer that will allow towers to shoot
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(aquireTarget()));
    m_timer->start(1000);

    // bullet sound
    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl((m_pathToBulletSound)));
}

QRectF Tower::boundingRect() const
{
    // (0, 0) is the center of the tower

    // this is just for the tower
    return QRectF(0 - m_towerSize/2, 0 - m_towerSize/1.5, m_towerSize, 1.5 * m_towerSize);

    // this is for the tower with radius included
//    return QRectF(0 - m_radius, 0 - m_radius, 2.0 * m_radius, 2.0 * m_radius);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // center of the item is (0, 0), or (x, y) on the scene

    // draw the radius of the tower
//    painter->drawEllipse(QPointF(0, 0), m_radius, m_radius);

    // draw the tower
    QPixmap pixmap(m_pathToImg);
    painter->drawPixmap(-m_towerSize/2, int(-m_towerSize/1.5), m_towerSize, int(1.5*m_towerSize), pixmap);
}

void Tower::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    int gold = m_price / 2;
    g->removeTower(this);
    g->increaseGold(gold);
    if(!m_draw_radius){
        g->scene->removeItem(ellipse);
    }

    delete this;
}

void Tower::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if (m_draw_radius) {
        ellipse = new QGraphicsEllipseItem(this->x()-100, this->y()-100, 200, 200);

        g->scene->addItem(ellipse);
        m_draw_radius = false;
    }
}

void Tower::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_draw_radius) {
        g->scene->removeItem(ellipse);
        m_draw_radius = true;
        delete ellipse;
    }
}

int Tower::price() const
{
    return m_price;
}

int Tower::towerSize() const
{
    return m_towerSize;
}

void Tower::fire()
{
    // shooting sounds
//    qDebug() << "pew pew pew";

    // create bullet, and animate shooting
    Bullet *bullet = new Bullet(m_target, x(), y(), m_damage);

    QLineF ln(QPointF(x(), y()), m_target->pos());
    qreal angle = -1 * ln.angle();

    bullet->setRotation(angle);
    bullet->setPixmap(QPixmap(m_pathToBulletImg));
    g->scene->addItem(bullet);

    // play bulletsound
    if (g->indicator) {
        if (bulletSound->state() == QMediaPlayer::PlayingState){
            bulletSound->setPosition(0);
        }
        else if (bulletSound->state() == QMediaPlayer::StoppedState){
            bulletSound->play();
        }
    }
}

void Tower::aquireTarget()
{
    // there are enemies we can shoot
    if (! g->enemiesByType(m_type).empty()) {
        // if the target is not alive, we choose the new one
        if (! g->enemiesByType(m_type).contains(m_target)) {
            findClosestEnemy();
        }

        // distance between the tower and the target
        qreal dist = QLineF(pos(), m_target->pos()).length();

        if (dist < 1.5*m_radius) {
            // if the target is in the range, shoot it
            fire();
        } else {
            // if it is not, then find new one
            findClosestEnemy();
        }
    }
}

void Tower::findClosestEnemy()
{
    qreal minDist = double(INFINITY);
    for (auto i = g->enemiesByType(m_type).cbegin(); i != g->enemiesByType(m_type).cend(); ++i) {
        qreal currentDist = QLineF(pos(), (*i)->pos()).length();
        if (minDist > currentDist) {
            minDist = currentDist;
            m_target = std::move(*i);
        }
    }
}

Tower::~Tower()
{
    delete m_timer;
}
