#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "watchtowericon.h"
#include "arrowtowericon.h"
#include "enemies.h"
#include "icetowericon.h"
#include "magetowericon.h"
#include "witchtowericon.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>
#include <QApplication>
#include <QLabel>

Game::Game(QString pathToJson, QString pathToBackground, QString pathToRoadImage): QGraphicsView()
{
    // disable "X" button
    setWindowFlags(Qt::WindowTitleHint);

    // create and set the scene and view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1300, 700);

    QGraphicsRectItem *rect1 = scene->addRect(0, 0, 200, 700);
    rect1->setBrush(QBrush(QImage(":/images/background.png")));

    QGraphicsRectItem *rect2 = scene->addRect(200, 0, 1100, 650);
//    rect2->setBrush(QBrush(QImage(":/images/grass_6.jpeg")));
    rect2->setBrush(QBrush(QImage(":/images/" + pathToBackground)));

    setScene(scene);
    setFixedSize(1300, 700);

    // scroll disabled
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    cursor = nullptr;
    tower = nullptr;
    setMouseTracking(true);

    QGraphicsRectItem *rect3 = scene->addRect(0, 650, 1300, 50);
    rect3->setBrush(QBrush(QImage(":/images/map.jpg")));

    // initialize score
    m_score = new Score();
    m_score->setPos(10, 650);
    scene->addItem(m_score);

    // initialize number of lives
    m_lives = new Lives();
    m_lives->setPos(230, 650);
    scene->addItem(m_lives);

    // tower icons, this is where you buy towers
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

    initializeLevel(pathToJson);

    // pressing this button will start new wave
    QPushButton *button = new QPushButton(tr("Attack"));
    button->resize(90,40);
    button->move(56,575);
    button->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                          "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");
    scene->addWidget(button);
    connect(button, &QPushButton::clicked, this, &Game::playLevel);

//    this button will turn off the application
    QPushButton *resetButton = new QPushButton(tr("Reset"));
    resetButton->resize(90,40);
    resetButton->move(1200,655);
    resetButton->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                          "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");
    scene->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, &Game::resetGame);

//    esc key exits application
    QAction *exitKey = new QAction(this);
    exitKey->setShortcut(Qt::Key_Escape);

//    connect(exitKey, SIGNAL(triggered()), this, SLOT(close()));
    connect(exitKey, SIGNAL(triggered()), this, SLOT(escExit()));
    this->addAction(exitKey);

//    play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/soundtrack.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

//    mute sound
    muteButton = new QPushButton(tr("Mute"));
    muteButton->resize(100,40);
    muteButton->move(1095,655);
    muteButton->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                          "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");
    scene->addWidget(muteButton);
    connect(muteButton, &QPushButton::clicked, this, &Game::mute);

    drawEnemyPath(pathToRoadImage);

    m_notification = new Notifications();
    m_notification->setPos(600, 655);
    scene->addItem(m_notification);
}

void Game::initializeLevel(QString path)
{
    // read json file
    QFile json(path/*":/paths/level_1.json"*/);
    json.open(QIODevice::ReadOnly);
    QString val = json.readAll();
    json.close();

    QJsonDocument qJson = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject set = qJson.object();
    QJsonValue pathToFile = set.value("enemyPath");
    //qDebug() << path_to_file.toString();

    QJsonValue gold = set.value(QString("gold"));
//    m_gold = new Gold(gold.toInt());
     m_gold = new Gold(2000);
    m_gold->setPos(410, 650);
    scene->addItem(m_gold);

    //enemy's moving path initialize
    QFile file(pathToFile.toString());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(" ");
        m_path << QPoint(list[0].toInt(), list[1].toInt());
            //qDebug() << x << "," << y;
        }
    file.close();

    m_waves = set["waves"].toArray();

    m_waveNumber = 0;
    m_numberOfWaves = m_waves.size();
    m_waveInProgress = false;

}


void Game::playLevel()
{
    // if there is a wave active, you can't start a new one
    if (m_waveInProgress) {
        m_notification->setMessageAndDisplay("Spawning isn't finished!");
        return ;
    }

    // if all of the waves are finished, and there are no enemies, you won!
    if (m_waveNumber >= m_numberOfWaves && m_enemies.empty()) {
        int result = score() + lives() * gold();
        gameIsOver("Congratulations!", result);

        return ;
    }

    if (m_waveNumber >=/*==*/ m_numberOfWaves) {
        // we want to wait until all of the enemies are destroyed
        // in the last wave
        return ;
    }

    m_spawnTimer = new QTimer(this);
    m_enemiesSpawned = 0;
    m_maxNumberOfGoblins = m_waves[m_waveNumber].toArray().at(0).toInt();
    m_maxNumberOfCommonKnights = m_waves[m_waveNumber].toArray().at(1).toInt();
    m_maxNumberOfDarkKnights = m_waves[m_waveNumber].toArray().at(2).toInt();
    m_maxNumberOfZombieDinos = m_waves[m_waveNumber].toArray().at(3).toInt();
    m_maxNumberOfMoths = m_waves[m_waveNumber].toArray().at(4).toInt();
    m_maxNumberOfDragons = m_waves[m_waveNumber].toArray().at(5).toInt();
    m_maxNumberOfZombieDragons = m_waves[m_waveNumber].toArray().at(6).toInt();
    createEnemies();

    // notify the user about nember of enemies in the wave
    int numOfGround = m_maxNumberOfGoblins + m_maxNumberOfCommonKnights +
            m_maxNumberOfDarkKnights + m_maxNumberOfZombieDinos;
    int numOfFlying = m_maxNumberOfMoths + m_maxNumberOfDragons + m_maxNumberOfZombieDragons;
    m_notification->setMessageAndDisplay("Wave No: " + QString::number(m_waveNumber + 1) +
                                         ", Ground: " + QString::number(numOfGround) +
                                         ", Flying: " + QString::number(numOfFlying));
    m_waveNumber++;
}

void Game::createEnemies()
{
    //m_enemiesSpawned = 0;
    m_waveInProgress = true;
    connect(m_spawnTimer, SIGNAL(timeout()), this, SLOT(spawn_enemy()));
    m_spawnTimer->start(1100);
}

void Game::gameIsOver(QString msg, int result)
{
    GameOver *go = new GameOver();
    // int result = g->score() + g->lives() * g->gold();
    go->setText(msg, result);
    go->show();

    // game is over, delete remaining units
    deleteTowers();

    // hide the scene and mute music
    music->setMuted(true);
    hide();
}

int Game::score() const
{
    return m_score->getScore();
}

int Game::lives() const
{
    return m_lives->getHealth();
}

int Game::gold() const
{
    return m_gold->getGold();
}

void Game::spawn_enemy()
{
    // we are multiply enemy health with this value
    qreal multiplier = 1.0;
    // after the tenth wave, we want our enemies to be stronger
    if (m_waveNumber >= 10) {
        multiplier = 1.7;
    }

    // spawn an enemy
    if (m_maxNumberOfDarkKnights) {
        Enemy * e = new DarkKnight(m_path);
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfDarkKnights--;
        return;
    }
    if (m_maxNumberOfZombieDinos) {
        Enemy * e = new ZombieDino(m_path);
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfZombieDinos--;
        return;
    }
    if (m_maxNumberOfGoblins) {
        Enemy * e = new Goblin(m_path);
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfGoblins--;
        return;
    }
    if (m_maxNumberOfCommonKnights) {
        Enemy * e = new CommonKnight(m_path);
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfCommonKnights--;
        return;
    }
    if (m_maxNumberOfMoths) {
        Enemy * e = new Moth();
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfMoths--;
        return;
    }
    if (m_maxNumberOfDragons) {
        Enemy * e = new Dragon();
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfDragons--;
        return;
    }
    if (m_maxNumberOfZombieDragons) {
        Enemy * e = new ZombieDragon();
        e->setMaxHealth(int(e->maxHealth() * multiplier));

        scene->addItem(e);
        addEnemy(e);
        m_maxNumberOfZombieDragons--;
        return;
    }

    if (!m_maxNumberOfGoblins && !m_maxNumberOfCommonKnights && !m_maxNumberOfDarkKnights
            && !m_maxNumberOfZombieDinos && !m_maxNumberOfMoths && !m_maxNumberOfDragons
            && !m_maxNumberOfZombieDragons) {
        m_waveInProgress = false;
        m_spawnTimer->disconnect();
    }
}

void Game::drawEnemyPath(QString pathToRoadImage)
{
    QVector<QPoint> points;
    int pathSize = 25;

    // points from the right side of the enemy
    for (int i = 0; i < m_path.size(); ++i) {
        QPoint point = m_path[i];

        if (i == 0) {
            QPoint nextPoint = m_path[i+1];
            if (nextPoint.y() == point.y()) {
                point.setY(point.y() + pathSize);
            } else if (nextPoint.x() == point.x()) {
                point.setX(point.x() - pathSize);
            }
        } else if (i == m_path.size()-1) {
            QPoint previousPoint = m_path[i-1];
            if (previousPoint.y() == point.y()) {
                point.setY(point.y() - pathSize);
            } else if (previousPoint.x() == point.x()) {
                point.setX(point.x() - pathSize);
            }
        } else {
            QPoint nextPoint = m_path[i+1];
            QPoint previousPoint = m_path[i-1];

            if (point.y() == previousPoint.y()) {
                if (point.x() > previousPoint.x()) {
                    if (point.y() < nextPoint.y()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() + pathSize);
                    } else if (point.y() > nextPoint.y()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() + pathSize);
                    }
                } else {
                    if (point.y() < nextPoint.y()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() - pathSize);
                    } else if (point.y() > nextPoint.y()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() - pathSize);
                    }
                }
            } else if (point.x() == previousPoint.x()) {
                if (point.y() > previousPoint.y()) {
                    if (point.x() < nextPoint.x()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() + pathSize);
                    } else if (point.x() > nextPoint.x()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() - pathSize);
                    }
                } else {
                    if (point.x() < nextPoint.x()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() + pathSize);
                    } else if (point.x() > nextPoint.x()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() - pathSize);
                    }
                }
            }
        }

        points.push_back(point);
    }

    // points from the left side of the enemy
    for (int i = m_path.size()-1; i >= 0; --i) {
        QPoint point = m_path[i];

        if (i == 0) {
            QPoint nextPoint = m_path[i+1];
            if (nextPoint.y() == point.y()) {
                point.setY(point.y() - pathSize);
            } else if (nextPoint.x() == point.x()) {
                point.setX(point.x() + pathSize);
            }
        } else if (i == m_path.size()-1) {
            QPoint previousPoint = m_path[i-1];
            if (previousPoint.y() == point.y()) {
                point.setY(point.y() + pathSize);
            } else if (previousPoint.x() == point.x()) {
                point.setX(point.x() + pathSize);
            }
        } else {
            QPoint nextPoint = m_path[i+1];
            QPoint previousPoint = m_path[i-1];

            if (point.y() == previousPoint.y()) {
                if (point.x() > previousPoint.x()) {
                    if (point.y() < nextPoint.y()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() - pathSize);
                    } else if (point.y() > nextPoint.y()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() - pathSize);
                    }
                } else {
                    if (point.y() < nextPoint.y()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() + pathSize);
                    } else if (point.y() > nextPoint.y()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() + pathSize);
                    }
                }
            } else if (point.x() == previousPoint.x()) {
                if (point.y() > previousPoint.y()) {
                    if (point.x() < nextPoint.x()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() - pathSize);
                    } else if (point.x() > nextPoint.x()) {
                        point.setX(point.x() + pathSize);
                        point.setY(point.y() + pathSize);
                    }
                } else {
                    if (point.x() < nextPoint.x()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() - pathSize);
                    } else if (point.x() > nextPoint.x()) {
                        point.setX(point.x() - pathSize);
                        point.setY(point.y() + pathSize);
                    }
                }
            }
        }

        points.push_back(point);
    }

    m_polyPath = QPolygon(points);
    scene->addPolygon(m_polyPath, QPen(Qt::darkGray), QBrush(QImage(":/images/" + pathToRoadImage)));
}

void Game::addTower(Tower *t)
{
    m_towers.push_back(std::move(t));
    m_towerCoords.push_back(t->pos());
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

void Game::removeTower(Tower *t)
{
    m_towers.removeOne(t);
    m_towerCoords.removeOne(t->pos());
}

bool Game::containsEnemy(Enemy *e)
{
    if (e->enemyType() == EnemyType::GROUND_ENEMY)
        return m_groundEnemies.contains(e);
    else
        return m_flyingEnemies.contains(e);
}

void Game::deleteTowers()
{
    for (auto & t : m_towers)
        delete t;
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
    else if (type == EnemyType::FLYING_ENEMY)
        return flyingEnemies();
    else
        return enemies();
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
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        delete cursor;
        cursor = nullptr;
        tower = nullptr;
    } else if (tower) {
        // we cant bulid in the field that represents store or lives/score/gold
        if (event->x() < 225 || event->x() > 1280 || event->y() > 600) {
            m_notification->setMessageAndDisplay("Can't build there!");
            return;
        }

        if (dropTowerCheck(event)) {
            m_notification->setMessageAndDisplay("Can't build there!");
            return ;
        }

        decreaseGold(tower->price());

        // add the tower to the scene and to the list of towers
        scene->addItem(tower);
        tower->setPos(event->pos());
        addTower(tower);

        delete cursor;
        cursor = nullptr;
        tower = nullptr;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}


bool Game::dropTowerCheck(QMouseEvent *event)
{
    // creating a vector of points that bounds event point
    QVector<QPoint> bound {QPoint(event->x() - 20, event->y()),
                QPoint(event->x() + 20, event->y()),
                QPoint(event->x(), event->y() + 35),
                QPoint(event->x(), event->y() - 20)};

    // if you want to build tower on the road, you cant
    for (int i = 0; i < bound.size(); ++i) {
        if (m_polyPath.containsPoint(bound[i], Qt::OddEvenFill)) {
            return true;
        }
    }

    // if there is already a tower where you want to place new one, you cant
    for (int i = 0; i < m_towerCoords.size(); ++i) {
        int size = tower->towerSize();
        QRect rect(int(m_towerCoords[i].x() - size/2), int(m_towerCoords[i].y() - size/2),
                   size, size);

        if (rect.contains(event->pos())) {
            return true;
        }
    }

    // you can place the tower where you want to
    return false;
}

void Game::resetGame()
{
    QApplication::quit();
    QProcess::startDetached(QApplication::arguments()[0], QApplication::arguments());
}

void Game::mute()
{
    if (music->isMuted()) {
        music->setMuted(false);
        muteButton->setText("Mute");
        indicator = true;
    }
    else {
        music->setMuted(true);
        muteButton->setText("Unmute");
        indicator = false;
    }
}

void Game::escExit()
{
    QApplication::quit();
}

Game::~Game()
{
    delete m_gold;
    delete m_score;
    delete m_lives;
    delete tower;
    delete cursor;
    delete scene;
    delete music;
    delete m_notification;
    delete m_spawnTimer;
}
