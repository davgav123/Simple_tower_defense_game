#ifndef WITCHTOWERICON_H
#define WITCHTOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class WitchTowerIcon: public QGraphicsPixmapItem
{
public:
    WitchTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // WITCHTOWERICON_H
