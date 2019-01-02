#include "icetowericon.h"
#include "towers.h"
#include "game.h"
#include <QGraphicsPixmapItem>

extern Game *g;

IceTowerIcon::IceTowerIcon(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setToolTip("Targets flying units");
    setPixmap(QPixmap(":/images/iceTowerForStore.png"));
}

void IceTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!g->tower){
        g->tower = new IceTower(event->pos().x(), event->pos().y());

        // if we have the gold to buy the tower, we can buy it
        if (g->getAmountOfGold() < g->tower->price()) {
            g->m_notification->setMessageAndDisplay("Not enough gold!");
            delete g->tower;
            g->tower = nullptr;
            return ;
        }

        g->setCursor(QString(":/images/iceTower.png"),
                     event->pos().x(), event->pos().y()+216);
    }
}

