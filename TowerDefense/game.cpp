#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "watchtower.h"
#include "watchtowericon.h"
#include "arrowtower.h"
#include "arrowtowericon.h"
#include "enemies.h"

Game::Game(): QGraphicsView()
{
    // create and set the scene and view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1400, 700);

    QGraphicsRectItem *rect1 = scene->addRect(0, 0, 200, 700);
    rect1->setBrush(QBrush(QImage(":/images/background.png")));

    setScene(scene);
    setFixedSize(1400, 700);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    cursor = nullptr;
    tower = nullptr;
    setMouseTracking(true);

    QGraphicsRectItem *rect2 = scene->addRect(0, 600, 200, 100);
    rect2->setBrush(QBrush(QImage(":/images/woodenBoardResized.jpg")));

    // initialize number of lives
    m_lives = new Lives();
    scene->addItem(m_lives);

    // initialize score
    m_score = new Score();
    scene->addItem(m_score);

    scene->addLine(200, 0, 200, 900);

    // initl level from json file... init waves, initGold etc
    initializeLevel();

    // tower icon, this is where you buy towers
    WatchTowerIcon * watchTowerIcon = new WatchTowerIcon();
    scene->addItem(watchTowerIcon);

    ArrowTowerIcon * arrowTowerIcon = new ArrowTowerIcon();
    arrowTowerIcon->setPos(arrowTowerIcon->x(), arrowTowerIcon->y()+110);
    scene->addItem(arrowTowerIcon);

}

void Game::initializeLevel()
{
    // read json file
    QFile json(":/paths/path_1.json");
    json.open(QIODevice::ReadOnly);
    QString val = json.readAll();
    json.close();
    QJsonDocument q_json = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject set = q_json.object();
    QJsonValue path_to_file = set.value(QString("path_1"));
    //qDebug() << path_to_file.toString();

    QJsonValue gold = set.value(QString("gold"));

    // initialize gold
    m_gold = new Gold(gold.toInt());
    scene->addItem(m_gold);

    //enemy's moving path initialize
    QFile file(path_to_file.toString());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(" ");
        path << QPoint(list[0].toInt(), list[1].toInt());
            //qDebug() << x << "," << y;
        }
    file.close();

    QJsonArray waves = set["waves"].toArray();

    //qDebug() << waves[0];
    //int size = waves.size();
    spawnTimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfEnemies = 0;
    create_enemies(waves[0].toInt());
}

void Game::spawn_enemy(){
    // spawn an enemy
    Enemy * e = new Goblin(path);
    scene->addItem(e);
    addEnemy(e);
    enemiesSpawned += 1;

    if (enemiesSpawned >= maxNumberOfEnemies){
        spawnTimer->disconnect();
    }
}


void Game::create_enemies(int numberOfEnemies){
    enemiesSpawned = 0;
    maxNumberOfEnemies = numberOfEnemies;
    connect(spawnTimer,SIGNAL(timeout()),this,SLOT(spawn_enemy()));
    spawnTimer->start(1000);
}


void Game::addTower(Tower *t)
{
    m_towers.push_back(std::move(t));
//    qDebug() << "---- towers";
//    for (const auto & tower : m_towers)
//        qDebug() << tower->pos();
}

void Game::addEnemy(Enemy *e)
{
    m_enemies.push_back(std::move(e));
//    qDebug() << "---- enemies";
//    for (const auto & enemy : m_enemies)
//        qDebug() << enemy->pos();
}


void Game::removeEnemy(Enemy *e)
{
    m_enemies.removeOne(e);
//    for (const auto & e: m_enemies)
//        qDebug() << e->pos();
}

bool Game::containsEnemy(Enemy *e)
{
    return m_enemies.contains(e);
}

QLinkedList<Enemy *> Game::enemies() const
{
    return m_enemies;
}

void Game::increaseScore(int score)
{
    m_score->increase(score);
}

void Game::decreaseLives()
{
    m_lives->decrease();
}

void Game::increaseGold(int amount)
{
    m_gold->increaseGold(amount);
}

void Game::decreaseGold(int amount)
{
    m_gold->decreaseGold(amount);
}

int Game::getAmountOfGold() const
{
    return m_gold->getGold();
}

void Game::setCursor(QString filename, qreal x, qreal y)
{
    if (cursor) {
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPos(x, y); //ovde menjao
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (tower) {
        // if the tower is worth more than you have gold, then you cannot build the tower
        if (getAmountOfGold() < tower->price()) {
            qDebug() << "not enough gold";
            return ;
        }

        decreaseGold(tower->price());

        if (event->pos().x() < 220) {
            return;
        }

        // add the tower to the scene and to the list of towers
        scene->addItem(tower);
        tower->setPos(event->pos());
        addTower(tower);

        delete cursor;
        cursor = nullptr;
        tower = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
