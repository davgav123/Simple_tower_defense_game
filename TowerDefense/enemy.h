#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QString>

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    Enemy(QVector<QPoint> path, qreal speed, int maxHealth, int worth, QString pathToImg, QString pathToFlippedImg);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void decreaseHealth(int amount);

private slots:
    void move();

private:
    QVector<QPoint> m_path;
    int m_currentFromIndex;
    int m_currentDestIndex;
    QPoint m_currentFrom;
    QPoint m_currentDest;

    qreal m_size;
    qreal m_healthBarDistance;
    // m_speed must be dividable by 10 or 5 or 2
    qreal m_speed;

    qreal m_maxHealth;
    qreal m_currentHealth;

    int m_worthInGold;

    QString m_pathToImage;
    QString m_pathToFlippedImage;
    QString m_currentImage;

    void destroyTheEnemy();
};

#endif // ENEMY_H
