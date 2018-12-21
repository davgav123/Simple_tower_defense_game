#include "game.h"
#include "tower.h"
#include "enemy.h"

#include <QDebug>

Game::Game()
{
    // create and set the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 900);

    setScene(scene);
    setFixedSize(1400, 900);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Tower *t = new Tower(30, 120);
    scene->addItem(t);
    // mem leak...

    Enemy * e = new Enemy();
//    enemy = new Enemy();
    scene->addItem(e);
    addEnemy(e);
}

void Game::addTower(Tower *t)
{
    m_towers.push_back(std::move(t));
//    qDebug() << "---- towers";
//    for (const auto & tower : m_towers)
//        qDebug() << tower->pos();
}

void Game::addEnemy(Enemy *e)
{
    m_enemies.push_back(std::move(e));
//    qDebug() << "---- enemies";
//    for (const auto & enemy : m_enemies)
//        qDebug() << enemy->pos();
}


void Game::removeEnemy(Enemy *e)
{
    m_enemies.removeOne(e);
    for (const auto & e: m_enemies)
        qDebug() << e->pos();
}

QLinkedList<Enemy *> Game::enemies() const
{
    return m_enemies;
}

QVector<Tower *> Game::towers() const
{
    return m_towers;
}
