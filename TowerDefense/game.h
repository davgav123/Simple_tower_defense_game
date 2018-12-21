#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "enemy.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QLinkedList>

class Game: public QGraphicsView
{
public:
    Game();

    QGraphicsScene * scene;

    void addTower(Tower *t);
    void addEnemy(Enemy *e);

    QVector<Tower*> towers() const;
    QLinkedList<Enemy*> enemies() const;

    void removeEnemy(Enemy *e);
private:
    QVector<Tower*> m_towers;
    QLinkedList<Enemy*> m_enemies;


};

#endif // GAME_H
