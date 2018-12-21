#ifndef TOWERICON_H
#define TOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class TowerIcon: public QGraphicsPixmapItem
{
public:
    TowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOWERICON_H
