#ifndef GOLD_H
#define GOLD_H

#include "gameover.h"
#include <QGraphicsTextItem>
#include <QObject>
#include <QFont>
#include <QLabel>

class Gold: public QGraphicsTextItem
{
public:
    Gold(int initAmount);
    void decreaseGold(int amount);
    void increaseGold(int amount);
    int getGold() const;
private:
    int m_goldAmount;
};

class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent = nullptr);
    void increase(int score);
    int getScore();
private:
    int m_score;
};

class Lives: public QGraphicsTextItem
{
public:
    Lives(QGraphicsItem * parent = nullptr);
    void decrease();
    int getHealth();
private:
    int m_numberOfLives;
};

class Notifications : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Notifications();
    ~Notifications();

    void setMessageAndDisplay(QString message);
public slots:
    void display();
private:
    QTimer *m_displayTimer;

    QString m_message;
};

#endif // GOLD_H
