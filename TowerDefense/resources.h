#ifndef GOLD_H
#define GOLD_H

#include <QGraphicsTextItem>

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

#endif // GOLD_H
