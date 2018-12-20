#include "game.h"
#include "tower.h"
#include "enemy.h"

Enemy *enemy;

Game::Game(): QGraphicsView()
{
    // create and set the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 900);

    setScene(scene);
    setFixedSize(1600, 900);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Tower *t = new Tower(30, 120);
    scene->addItem(t);
    // mem leak...

    Tower *t2 = new Tower(30, 330);
    scene->addItem(t2);

//    Enemy * e = new Enemy();
    enemy = new Enemy();
    scene->addItem(enemy);
}
