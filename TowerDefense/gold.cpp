#include "gold.h"
#include <QFont>

Gold::Gold(int initAmount)
    : m_goldAmount(initAmount)
{
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
