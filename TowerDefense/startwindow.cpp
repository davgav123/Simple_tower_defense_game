#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle("Start screen");

    // set background
    QPixmap backgroundImg(":/images/pavedRoad.jpg");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

//    this->setStyleSheet("#centralWidget {background-image: url(:/images/pavedRoad.jpg);"
//                        "background-position: center;}");

    // set button styles
    ui->FirstLevel->setStyleSheet("QPushButton {background-color: rgb(30, 30, 30); margin: 3px;"
                               "color: rgb(200, 200, 200); font-weight: bold; font-size: 24px; font-style: italic;}");
    ui->Quit->setStyleSheet("QPushButton {background-color: rgb(30, 30, 30); margin: 3px;"
                            "color: rgb(200, 200, 200); font-weight: bold; font-size: 24px; font-style: italic;}");


    // connect buttons to functions
    connect(ui->FirstLevel, SIGNAL(clicked()), SLOT(startLevelOne()));
    connect(ui->Quit, SIGNAL(clicked()), SLOT(quitGame()));
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::startLevelOne() const
{
    g = new Game();
    g->show();
}

void StartWindow::quitGame()
{
//    delete g; <- TODO
    QApplication::quit();
}
