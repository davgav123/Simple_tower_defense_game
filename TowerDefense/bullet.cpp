#include "bullet.h"
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem *parent)
{
    setRect(0, 0, 10, 10);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
