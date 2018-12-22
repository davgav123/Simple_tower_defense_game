#include "watchtowericon.h"
#include "game.h"
#include "towericon.h"
#include "watchtower.h"
#include <QGraphicsPixmapItem>

extern Game *g;

WatchTowerIcon::WatchTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/towerStore_1.png"));
}

void WatchTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new WatchTower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/tower4.png"),
                     event->pos().x(), event->pos().y());
    }
}


