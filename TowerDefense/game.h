#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "enemy.h"
#include "resources.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QLinkedList>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsPathItem>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void addTower(Tower *t);
    void addEnemy(Enemy *e);
    void removeEnemy(Enemy *e);
    bool containsEnemy(Enemy *e);
    void create_enemies(int numberOfEnemies);

    QLinkedList<Enemy*> enemies() const;

    void increaseScore(int score);
    void decreaseLives();
    void increaseGold(int amount);
    void decreaseGold(int amount);
    int getAmountOfGold() const;

    void setCursor(QString filename, qreal x, qreal y);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);


    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Tower *tower;
public slots:
    void spawn_enemy();
private:
    QVector<Tower*> m_towers;
    QLinkedList<Enemy*> m_enemies;

    Lives * m_lives;
    Score * m_score;
    Gold * m_gold;

    QTimer * spawnTimer;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QVector<QPoint> path;

    void initializeLevel();
};

#endif // GAME_H
