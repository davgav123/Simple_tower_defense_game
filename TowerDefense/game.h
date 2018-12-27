#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "enemy.h"
#include "resources.h"
#include "towers.h"
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
#include <QKeyEvent>
#include <QAction>
#include <QPolygon>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    ~Game();
    void addTower(Tower *t);
    void addEnemy(Enemy *e);
    void removeEnemy(Enemy *e);
    bool containsEnemy(Enemy *e);

    QLinkedList<Enemy*> groundEnemies() const;
    QLinkedList<Enemy*> flyingEnemies() const;
    QLinkedList<Enemy*> enemies() const;
    QLinkedList<Enemy*> enemiesByType(EnemyType type) const;

    void increaseScore(int score);
    void decreaseLives();
    void increaseGold(int amount);
    void decreaseGold(int amount);
    int getAmountOfGold() const;

    void setCursor(QString filename, qreal x, qreal y);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void playLevel();
    void exitGame();
    void mute();
    void createEnemies();

    bool indicator;

    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Tower *tower;
    Notifications *m_notification;
    QVector<Tower*> m_towers;
    QVector<QPointF> m_towerCoords;
public slots:
    void spawn_enemy();
private:


    QLinkedList<Enemy *> m_groundEnemies;
    QLinkedList<Enemy *> m_flyingEnemies;
    QLinkedList<Enemy *> m_enemies;

    Lives * m_lives;
    Score * m_score;
    Gold * m_gold;
    QMediaPlayer *music;

    QTimer * m_spawnTimer;
    int m_enemiesSpawned;
    int m_maxNumberOfGoblins;
    int m_maxNumberOfCommonKnights;
    int m_maxNumberOfDarkKnights;
    int m_maxNumberOfZombieDinos;
    int m_maxNumberOfRockets;
    int m_maxNumberOfDragons;
    int m_maxNumberOfZombieDragons;
    int m_waveNumber;
    int m_numberOfWaves;

    QJsonArray m_waves;
    int m_rocketsSpawned;
    int m_zombiesSpawned;
    QVector<QPoint> m_path;
    QPolygon m_polyPath;

    void initializeLevel();
    void drawEnemyPath();
};

#endif // GAME_H
