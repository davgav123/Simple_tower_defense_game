#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Bullet: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);
public slots:
    void move();
};

#endif // BULLET_H
