#include "resources.h"
#include <QFont>

Gold::Gold(int initAmount)
    : m_goldAmount(initAmount)
{
    setPos(20, 660);
    setPlainText(QString("Gold: ") + QString::number(m_goldAmount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));
}

void Gold::decreaseGold(int amount)
{
    m_goldAmount -= amount;
    setPlainText(QString("Gold: ") + QString::number(m_goldAmount));
}

void Gold::increaseGold(int amount)
{
    m_goldAmount += amount;
    setPlainText(QString("Gold: ") + QString::number(m_goldAmount));
}

int Gold::getGold() const
{
    return m_goldAmount;
}

Score::Score(QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_score(0)
{
    // draw the text
    setPos(20, 600);
    setPlainText(QString("Score: ") + QString::number(m_score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));
}

void Score::increase(int score)
{
    m_score += score;
    setPlainText(QString("Score: ") + QString::number(m_score));
}

int Score::getScore()
{
    return m_score;
}

Lives::Lives(QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_numberOfLives(10)
{
    // draw the text
    setPos(20, 630);
    setPlainText(QString("Lives: ") + QString::number(m_numberOfLives));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));
}

void Lives::decrease()
{
    m_numberOfLives--;
    setPlainText(QString("Lives: ") + QString::number(m_numberOfLives));
}

int Lives::getHealth()
{
    return m_numberOfLives;
}

