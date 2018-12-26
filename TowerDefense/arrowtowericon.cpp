#include "arrowtowericon.h"
#include "game.h"
#include "towers.h"
#include "resources.h"
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
    if (!g->tower) {
        g->tower = new ArrowTower(event->pos().x(), event->pos().y());

        // if we have the gold to buy the tower, we can buy it
        if (g->getAmountOfGold() < g->tower->price()) {
            // notify the user about this <- TODO
//            delete g->m_notification;
//            g->m_notification = new Notifications("Not enough gold!");
//            g->m_notification->setPos(630, 655);
//            g->scene->addItem(g->m_notification);
            qDebug() << "not enough gold";
            delete g->tower;
            g->tower = nullptr;
            return ;
        }

        g->setCursor(QString(":/images/japaneseTowerForCursor.png"),
                     event->pos().x(), event->pos().y()+106);
    }
}
