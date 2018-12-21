#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Lives: public QGraphicsTextItem
{
public:
    Lives(QGraphicsItem * parent = nullptr);
    void decrease();
    int getHealth();
private:
    int m_numberOfLives;
};

#endif // HEALTH_H
