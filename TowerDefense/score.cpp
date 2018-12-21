#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_score(0)
{
    // draw the text
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
