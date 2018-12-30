#include "resources.h"
#include "game.h"

extern Game *g;

Gold::Gold(int initAmount)
    : m_goldAmount(initAmount)
{
    setPos(20, 660);
    setPlainText(QString("Gold: ") + QString::number(m_goldAmount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("sans serif", 26, QFont::StyleItalic, true));
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
    setFont(QFont("sans serif", 26, QFont::StyleItalic, true));
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
    setPlainText(QString("Lives: ") + QString::number(m_numberOfLives));
    setFont(QFont("sans serif", 26, QFont::StyleItalic, true));
}

void Lives::decrease()
{
    m_numberOfLives--;

    if (m_numberOfLives == 0) {
        g->gameIsOver("GAME OVER!", g->score());

        return ;
    }

    setPlainText(QString("Lives: ") + QString::number(m_numberOfLives));
}

int Lives::getHealth()
{
    return m_numberOfLives;
}


Notifications::Notifications()
{
    // draw the text
    setPlainText("");
    setDefaultTextColor(Qt::red);
    setFont(QFont("sans serif", 20, QFont::StyleItalic, true));

    m_displayTimer = new QTimer(this);
    connect(m_displayTimer, SIGNAL(timeout()), this, SLOT(display()));
}

Notifications::~Notifications()
{
    delete m_displayTimer;
}

void Notifications::setMessageAndDisplay(QString message)
{
    m_message = message;
    setPlainText(m_message);
    m_displayTimer->start(1000);
}

void Notifications::display()
{
    static int iters = 0;
    setPlainText(m_message);

    if (iters >= 2) {
        m_displayTimer->stop();
        iters = 0;
        setPlainText("");
        return ;
    }

    iters++;
}
