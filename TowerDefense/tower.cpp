#include "tower.h"

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QtMath>

#include <QDebug>

Tower::Tower(QGraphicsItem *parent)
    : range(100), scale_tower(100)
{
    // set tower image
    QPixmap towerImg = QPixmap(":/images/jigglypuff.png").scaled(scale_tower, scale_tower);
    setPixmap(towerImg);

    // create tower radius
    int radius_center_x = 0;
    int radius_center_y = 0;
    QVector<QPointF> points;
    int num_of_dots = 100;
    for (int i = 0; i < num_of_dots; i++) {
        points.push_back(QPointF(qCos(2 * i * 3.1415926535 / num_of_dots)  * range + radius_center_x,
                  qSin(2 * i * 3.1415926535 / num_of_dots) * range + radius_center_y));
    }
    attack_area = new QGraphicsPolygonItem(QPolygonF(points), this);

    // move the polygon
    QPointF poly_center(radius_center_x, radius_center_y);
    poly_center = mapToScene(poly_center);

    QPointF tower_center(x() + towerImg.width() / 2.0, y() + towerImg.height() / 2.0);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x() + ln.dx(), y() + ln.dy());



}
