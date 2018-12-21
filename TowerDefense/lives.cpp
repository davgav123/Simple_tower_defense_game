#include "lives.h"
#include <QFont>

Lives::Lives(QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_numberOfLives(10)
{
    // draw the text
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

