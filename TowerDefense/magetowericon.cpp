#include "magetowericon.h"
#include "magetower.h"
#include "game.h"
#include <QGraphicsPixmapItem>

extern Game *g;

MageTowerIcon::MageTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mageTowerForStore.png"));
}

void MageTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new MageTower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/mage.png"),
                     event->pos().x(), event->pos().y()+436);
    }
}


