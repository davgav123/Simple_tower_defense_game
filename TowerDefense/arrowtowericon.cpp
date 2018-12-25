#include "arrowtowericon.h"
#include "game.h"
#include "towers.h"
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

extern Game *g;

ArrowTowerIcon::ArrowTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/japaneseTowerStore_2.png"));
}

void ArrowTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new ArrowTower(event->pos().x(), event->pos().y());
        g->setCursor(QString(":/images/japaneseTowerForCursor.png"),
                     event->pos().x(), event->pos().y()+106);
    }
}
