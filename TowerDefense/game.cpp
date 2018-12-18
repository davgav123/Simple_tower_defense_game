#include "game.h"
#include <QGraphicsScene>
#include "tower.h"

Game::Game()
{
    // create a scene
    scene = new QGraphicsScene(this);
//    scene->setSceneRect(0, 0, 800, 600);

    // set the scene
    setScene(scene);

    // create a tower
    Tower * t = new Tower();
    // mem leak

    // add the tower to the scene
    scene->addItem(t);

    setFixedSize(400, 400);
}
