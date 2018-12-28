#include "startwindow.h"
#include "ui_startwindow.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle("Start screen");

    this->setFixedSize(900, 550);
    // set background
//    QPixmap backgroundImg(":/images/introImage_2.jpg");
    QPixmap backgroundImg(":/images/introImage_1.png");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

//    this->setStyleSheet("#centralWidget {background-image: url(:/images/pavedRoad.jpg);"
//                        "background-position: center;}");

    // set button styles
    ui->FirstLevel->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                                  "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->SecondLevel->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->ThirdLevel->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->Quit->setStyleSheet("QPushButton {background-color: orange; margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");


    // connect buttons to functions
    connect(ui->FirstLevel, SIGNAL(clicked()), SLOT(startLevelOne()));
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

void StartWindow::startLevelOne() const
{
    if (music) {
        music->stop();
    }

    g = new Game();
    g->show();
}

void StartWindow::quitGame()
{
//    delete g; <- TODO
    QApplication::quit();
}
