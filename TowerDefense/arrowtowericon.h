#ifndef ARROWTOWERICON_H
#define ARROWTOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ArrowTowerIcon: public QGraphicsPixmapItem
{
public:
    ArrowTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ARROWTOWERICON_H
