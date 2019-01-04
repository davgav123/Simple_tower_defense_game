#ifndef ARROWTOWERICON_H
#define ARROWTOWERICON_H

#include "game.h"
#include "towers.h"
#include "resources.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class ArrowTowerIcon: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ArrowTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


#endif // ARROWTOWERICON_H
