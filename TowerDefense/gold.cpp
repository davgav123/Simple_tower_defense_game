#include "gold.h"
#include <QFont>

Gold::Gold()
    : m_goldAmount(500)
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

int Gold::getGold()
{
    return m_goldAmount;
}
