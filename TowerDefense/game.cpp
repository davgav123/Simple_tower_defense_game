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
    // create and set the scene and view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 700);

    QGraphicsRectItem *rect1 = scene->addRect(0, 0, 200, 700);
    rect1->setBrush(QBrush(QImage(":/images/background.png")));

    setScene(scene);
    setFixedSize(1400, 700);

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

    m_gold = new Gold(400);
    m_gold->setPos(20, 660);
    scene->addItem(m_gold);

    scene->addLine(200, 0, 200, 900);

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

    // init enemy, more enemies will be added
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

void Game::increaseGold(int amount)
{
    m_gold->increaseGold(amount);
}

void Game::decreaseGold(int amount)
{
    m_gold->decreaseGold(amount);
}

int Game::getAmountOfGold() const
{
    return m_gold->getGold();
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
    if (tower) {
        // if the tower is worth more than you have gold, then you cannot build the tower
        if (getAmountOfGold() < tower->price()) {
            qDebug() << "not enough gold";
            return ;
        }

        decreaseGold(tower->price());

        if (event->pos().x() < 220) {
            return;
        }

        // add the tower to the scene and to the list of towers
        scene->addItem(tower);
        tower->setPos(event->pos());
        addTower(tower);

        delete cursor;
        cursor = nullptr;
        tower = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
