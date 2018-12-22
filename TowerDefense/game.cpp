#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "lives.h"
#include "score.h"
#include "gold.h"
#include "towericon.h"
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

Game::Game()
{
    // create and set the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 900);

    QGraphicsRectItem *rect1 = scene->addRect(0, 0, 200, 900);
    rect1->setBrush(QBrush(QImage(":/images/background.png")));

    setScene(scene);
    setFixedSize(1400, 900);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    cursor = nullptr;
    tower = nullptr;
    setMouseTracking(true);

    QGraphicsRectItem *rect2 = scene->addRect(0, 600, 200, 100);
    rect2->setBrush(QBrush(QImage(":/images/woodenBoardResized.jpg")));

    // initialize number of lives
    m_lives = new Lives();
    m_lives->setPos(20, 630);
    scene->addItem(m_lives);

    // initialize score
    m_score = new Score();
    m_score->setPos(20, 600);
    scene->addItem(m_score);

    m_gold = new Gold();
    m_gold->setPos(20, 660);
    scene->addItem(m_gold);

    scene->addLine(200, 0, 200, 900);

    // init enemy, more enemies will be added
    QFile file(":/paths/path_1.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QVector<QPoint> path;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(" ");

        int x = list[0].toInt();
        int y = list[1].toInt();
        path << QPoint(x, y);
        qDebug() << x << "," << y;
    }
    file.close();
    Enemy * e = new Enemy(path);
//    enemy = new Enemy();
    scene->addItem(e);
    addEnemy(e);

    // tower icon, this is where you buy towers
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

bool Game::containsEnemy(Enemy *e)
{
    return m_enemies.contains(e);
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
