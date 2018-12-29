#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle("Start screen");

    this->setFixedSize(900, 550);

    // set background
//    QPixmap backgroundImg(":/images/introMap_3.jpg");
//    QPixmap backgroundImg(":/images/introMap_1.png");
    QPixmap backgroundImg(":/images/introMap_1_changed.png");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

    // set button styles
    ui->FirstLevel->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                                  "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->SecondLevel->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->ThirdLevel->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->Quit->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    // connect buttons to functions
    connect(ui->FirstLevel, SIGNAL(clicked()), SLOT(startLevelOne()));
    connect(ui->SecondLevel, SIGNAL(clicked()), SLOT(startLevelTwo()));
    connect(ui->ThirdLevel, SIGNAL(clicked()), SLOT(startLevelThree()));
    connect(ui->Quit, SIGNAL(clicked()), SLOT(quitGame()));

//    play music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/introMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::startLevelOne()
{
    if (music) {
        music->stop();
    }

    g = new Game(":/paths/level_1.json", "grass_6.jpeg", "road_1.jpg");
    g->show();

    hide();
}

void StartWindow::startLevelTwo()
{
    if (music) {
        music->stop();
    }

    g = new Game(":/paths/level_2.json", "forest_1.jpg", "forestRoad_2.jpg");
    g->show();

    hide();
}

void StartWindow::startLevelThree()
{
    if (music) {
        music->stop();
    }

    g = new Game(":/paths/level_3.json", "forest_1.jpg", "forestRoad_2.jpg");
    g->show();

    hide();
}

void StartWindow::quitGame()
{
    QApplication::quit();
}
