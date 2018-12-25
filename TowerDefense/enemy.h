#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QString>

enum EnemyType
{
    GROUND_ENEMY,
    FLYING_ENEMY
};

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Enemy(qreal speed, int maxHealth, int worth, QString currentImage, EnemyType type);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void decreaseHealth(int amount);
    void destroyTheEnemy();

    EnemyType enemyType() const;

    virtual ~Enemy() override;

protected slots:
    virtual void move() = 0;

protected:
    qreal m_size;
    qreal m_healthBarDistance;
    // m_speed must be 2, 2.5 or 5 <- because of the way enemy moves
    qreal m_speed;

    qreal m_maxHealth;
    qreal m_currentHealth;

    int m_worthInGold;

    QString m_currentImage;

    EnemyType m_type;
};

#endif // ENEMY_H
