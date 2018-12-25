#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "watchtower.h"
#include "watchtowericon.h"
#include "arrowtower.h"
#include "arrowtowericon.h"
#include "enemies.h"
#include "icetowericon.h"
#include "magetowericon.h"
#include "witchtowericon.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>

Game::Game(): QGraphicsView()
{
    // create and set the scene and view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1300, 700);

    QGraphicsRectItem *rect1 = scene->addRect(0, 0, 200, 700);
    rect1->setBrush(QBrush(QImage(":/images/background.png")));

    setScene(scene);
    setFixedSize(1300, 700);

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

    // tower icon, this is where you buy towers
    WatchTowerIcon * watchTowerIcon = new WatchTowerIcon();
    scene->addItem(watchTowerIcon);

    ArrowTowerIcon * arrowTowerIcon = new ArrowTowerIcon();
    arrowTowerIcon->setPos(arrowTowerIcon->x(), arrowTowerIcon->y()+110);
    scene->addItem(arrowTowerIcon);

    IceTowerIcon *iceTowerIcon = new IceTowerIcon();
    iceTowerIcon->setPos(iceTowerIcon->x(), iceTowerIcon->y()+220);
    scene->addItem(iceTowerIcon);

    WitchTowerIcon *witchTowerIcon = new WitchTowerIcon();
    witchTowerIcon->setPos(witchTowerIcon->x(), witchTowerIcon->y()+330);
    scene->addItem(witchTowerIcon);

    MageTowerIcon *mageTowerIcon = new MageTowerIcon();
    mageTowerIcon->setPos(mageTowerIcon->x(), mageTowerIcon->y()+440);
    scene->addItem(mageTowerIcon);
    level = 0;
    initializeLevel();
    QPushButton *button = new QPushButton(tr("Start"));
    button->resize(200,50);
    button->move(0,550);
    scene->addWidget(button);
    connect(
            button, &QPushButton::clicked,
            this  , &Game::playLevel
        );


    // play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/soundtrack.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer * music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
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

    waves = set["waves"].toArray();


//    qDebug() << waves[0].toArray().at(0).toInt();
    //int size = waves.size();

}

void Game::playLevel(){
    spawnTimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfZombies = 0;
    maxNumberOfRockets = 0;
    create_enemies(waves[level].toArray().at(0).toInt(), waves[level].toArray().at(1).toInt());
    level++;
}

void Game::spawn_enemy()
{
    // spawn an enemy
    if(zombiesSpawned < maxNumberOfZombies){
        Enemy * e = new ZombieDino(path);
        scene->addItem(e);
        addEnemy(e);
        zombiesSpawned += 1;
    }
    if(rocketsSpawned < maxNumberOfRockets){
        Enemy * e2 = new Rocket();
        scene->addItem(e2);
        addEnemy(e2);
        rocketsSpawned += 1;
    }

    enemiesSpawned += 1;

    if (enemiesSpawned >= (maxNumberOfZombies + maxNumberOfRockets)) {
        spawnTimer->disconnect();
    }
}


void Game::create_enemies(int numberOfZombies, int numberOfRockets)
{
    enemiesSpawned = 0;
    rocketsSpawned = 0;
    zombiesSpawned = 0;
    maxNumberOfZombies = numberOfZombies;
    maxNumberOfRockets = numberOfRockets;
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawn_enemy()));
    spawnTimer->start(1300);
}

void Game::addTower(Tower *t)
{
    m_towers.push_back(std::move(t));
}

void Game::addEnemy(Enemy *e)
{
    if (e->enemyType() == EnemyType::GROUND_ENEMY)
        m_groundEnemies.push_back(std::move(e));
    else
        m_flyingEnemies.push_back(std::move(e));

    m_enemies.push_back(std::move(e));
}

void Game::removeEnemy(Enemy *e)
{
    if (e->enemyType() == EnemyType::GROUND_ENEMY)
        m_groundEnemies.removeOne(e);
    else
        m_flyingEnemies.removeOne(e);

    m_enemies.removeOne(e);
}

bool Game::containsEnemy(Enemy *e)
{
    if (e->enemyType() == EnemyType::GROUND_ENEMY)
        return m_groundEnemies.contains(e);
    else
        return m_flyingEnemies.contains(e);
}

QLinkedList<Enemy *> Game::groundEnemies() const
{
    return m_groundEnemies;
}

QLinkedList<Enemy *> Game::flyingEnemies() const
{
    return m_flyingEnemies;
}

QLinkedList<Enemy *> Game::enemies() const
{
    return m_enemies;
}

QLinkedList<Enemy *> Game::enemiesByType(EnemyType type) const
{
    if (type == EnemyType::GROUND_ENEMY)
        return groundEnemies();
    else
        return flyingEnemies();
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
    cursor->setPos(x, y);
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


        if (event->pos().x() < 220 || event->pos().x() > 1280) {
            return;
        }

        decreaseGold(tower->price());

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
