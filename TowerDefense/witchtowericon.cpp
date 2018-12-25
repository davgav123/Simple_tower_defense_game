#include "witchtowericon.h"
#include "towers.h"
#include "game.h"
#include <QGraphicsPixmapItem>

extern Game *g;

WitchTowerIcon::WitchTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/witchTowerForStore.png"));
}

void WitchTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new WitchTower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/witch.png"),
                     event->pos().x(), event->pos().y()+326);
    }
}

