#ifndef MAGETOWERICON_H
#define MAGETOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class MageTowerIcon: public QGraphicsPixmapItem
{
public:
    MageTowerIcon(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAGETOWERICON_H
