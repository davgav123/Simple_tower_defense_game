#ifndef WATCHTOWERICON_H
#define WATCHTOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class WatchTowerIcon: public QGraphicsPixmapItem
{
public:
    WatchTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // WATCHTOWERICON_H
