#ifndef GROUNDENEMY_H
#define GROUNDENEMY_H

#include "enemy.h"
#include "game.h"

#include <QString>
#include <QTimer>

class GroundEnemy : public Enemy
{
public:
    GroundEnemy(QVector<QPoint> path, qreal speed, int maxHealth, int worth, QString pathToImg, QString pathToFlippedImg);

private slots:
    void move();

private:
    QVector<QPoint> m_path;
    int m_currentFromIndex;
    int m_currentDestIndex;
    QPoint m_currentFrom;
    QPoint m_currentDest;

    QString m_pathToImage;
    QString m_pathToFlippedImage;
};

#endif // GROUNDENEMY_H
