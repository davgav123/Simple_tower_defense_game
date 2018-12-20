#include "game.h"
#include "tower.h"
#include "enemy.h"

Game::Game()
{
    // create and set the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 900);

    setScene(scene);
    setFixedSize(1600, 900);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Tower *t = new Tower(400, 400);
    scene->addItem(t);
    // mem leak...

    Tower *t2 = new Tower(800, 200);
    scene->addItem(t2);

    Enemy * e = new Enemy();
    scene->addItem(e);
}
