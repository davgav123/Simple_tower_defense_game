#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "lives.h"
#include "score.h"
#include "towericon.h"
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

    cursor = nullptr;
    tower = nullptr;
    setMouseTracking(true);

    m_lives = new Lives();
    m_lives->setPos(20, 650);
    scene->addItem(m_lives);

    m_score = new Score();
    m_score->setPos(20, 600);
    scene->addItem(m_score);

//    QPixmap pixmap(200,900);
//    pixmap.fill(Qt::red);
//    scene->addPixmap(pixmap);
    scene->addLine(200, 0, 200, 900);

    Enemy * e = new Enemy();
//    enemy = new Enemy();
    scene->addItem(e);
    addEnemy(e);


    TowerIcon * towerIcon = new TowerIcon();
    scene->addItem(towerIcon);

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

void Game::setCursor(QString filename)
{
    if (cursor) {
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (tower){
        if (event->pos().x() < 220) {
            return;
        }
        scene->addItem(tower);
        tower->setPos(event->pos());
        delete cursor;
        cursor = nullptr;
        tower = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
