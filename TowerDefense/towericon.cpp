#include "game.h"
#include "towericon.h"
#include "tower.h"
#include <QGraphicsPixmapItem>

extern Game *g;

TowerIcon::TowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/towerStore_1.png"));
}

void TowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new Tower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/tower4.png"));
    }
}

