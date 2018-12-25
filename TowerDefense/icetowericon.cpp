#include "icetowericon.h"
#include "towers.h"
#include "game.h"
#include <QGraphicsPixmapItem>

extern Game *g;

IceTowerIcon::IceTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/iceTowerForStore.png"));
}

void IceTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new IceTower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/iceTower.png"),
                     event->pos().x(), event->pos().y()+216);
    }
}

