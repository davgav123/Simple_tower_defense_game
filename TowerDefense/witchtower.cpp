#include "witchtower.h"
#include "game.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>

extern Game *g;

WitchTower::WitchTower(qreal x, qreal y) :Tower(x, y, 20, 100, EnemyType::FLYING_ENEMY)
{
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(aquireTarget()));
    timer->start(1000);

    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl("qrc:/sounds/bulletSound.mp3"));
}

void WitchTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // draw the radius of the tower
    //painter->drawEllipse(tower_center, m_radius, m_radius);
    // draw the tower
    QPixmap pixmap(":/images/witch.png");
    painter->drawPixmap(-25, -35, 50, 70, pixmap);
}

void WitchTower::fire()
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

    // play bulletsound
    if (bulletSound->state() == QMediaPlayer::PlayingState){
        bulletSound->setPosition(0);
    }
    else if (bulletSound->state() == QMediaPlayer::StoppedState){
        bulletSound->play();
    }
}

void WitchTower::aquire_target()
{
    Tower::aquireTarget();
}


