#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "enemy.h"
#include "lives.h"
#include "score.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QLinkedList>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Game: public QGraphicsView
{
public:
    Game();
    void addTower(Tower *t);
    void addEnemy(Enemy *e);
    void removeEnemy(Enemy *e);
    bool containsEnemy(Enemy *e);

    QLinkedList<Enemy*> enemies() const;

    void increaseScore(int score);
    void decreaseLives();

    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Tower *tower;
private:
    QVector<Tower*> m_towers;
    QLinkedList<Enemy*> m_enemies;

    Lives * m_lives;
    Score * m_score;
};

#endif // GAME_H
