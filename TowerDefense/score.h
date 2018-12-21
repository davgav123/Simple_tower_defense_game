#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent = nullptr);
    void increase(int score);
    int getScore();
private:
    int m_score;
};

#endif // SCORE_H
