#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "lives.h"
#include "score.h"
#include <QPainter>
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

    m_lives = new Lives();
    m_lives->setPos(20, 650);
    scene->addItem(m_lives);

    m_score = new Score();
    m_score->setPos(20, 600);
    scene->addItem(m_score);

    Tower *t = new Tower(100, 80);
    scene->addItem(t);
    // mem leak...

//    QPixmap pixmap(200,900);
//    pixmap.fill(Qt::red);
//    scene->addPixmap(pixmap);
    scene->addLine(200, 0, 200, 900);

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

void Game::increaseScore(int score)
{
    m_score->increase(score);
}

void Game::decreaseLives()
{
    m_lives->decrease();
}
