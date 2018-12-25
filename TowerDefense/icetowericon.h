#ifndef ICETOWERICON_H
#define ICETOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class IceTowerIcon: public QGraphicsPixmapItem
{
public:
    IceTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ICETOWERICON_H
