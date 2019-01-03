#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "enemy.h"
#include "resources.h"
#include "towers.h"
#include "gameover.h"
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
#include <QProcess>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QString pathToJson, QString pathToBackground, QString pathToRoadImage);
    ~Game();
    void addTower(Tower *t);
    void addEnemy(Enemy *e);
    void removeEnemy(Enemy *e);
    void removeTower(Tower *t);
    bool containsEnemy(Enemy *e);
    void deleteTowers();

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
    void resetGame();
    void mute();
    void createEnemies();
    void gameIsOver(QString msg, int result);

    int score() const;
    int lives() const;
    int gold() const;

    bool indicator = true;
    QMediaPlayer *music;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Notifications *m_notification;
    Tower *tower;

public slots:
    void spawn_enemy();
    void escExit();

private:
    QLinkedList<Enemy *> m_groundEnemies;
    QLinkedList<Enemy *> m_flyingEnemies;
    QLinkedList<Enemy *> m_enemies;
    QVector<Tower*> m_towers;
    QVector<QPointF> m_towerCoords;

    Lives * m_lives;
    Score * m_score;
    Gold * m_gold;
    QPushButton *muteButton;
    QTimer * m_spawnTimer;
    int m_enemiesSpawned;
    int m_maxNumberOfGoblins;
    int m_maxNumberOfCommonKnights;
    int m_maxNumberOfDarkKnights;
    int m_maxNumberOfZombieDinos;
    int m_maxNumberOfMoths;
    int m_maxNumberOfDragons;
    int m_maxNumberOfZombieDragons;
    int m_waveNumber;
    int m_numberOfWaves;
    bool m_waveInProgress;

    QJsonArray m_waves;
    QVector<QPoint> m_path;
    QPolygon m_polyPath;


    void initializeLevel(QString path);
    void drawEnemyPath(QString pathToRoadImage);
    bool dropTowerCheck(QMouseEvent *event);
};

#endif // GAME_H
