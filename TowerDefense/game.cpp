#include "game.h"
#include "tower.h"

Game::Game()
{
    // create and set the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 800);

    setScene(scene);
    setFixedSize(800, 800);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Tower *t = new Tower(400, 400);
    scene->addItem(t);
    // mem leak...
}
