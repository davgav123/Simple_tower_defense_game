#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    setWindowTitle("Game over!");
    this->setFixedSize(400, 200);
    QPixmap backgroundImg(":/images/map.jpg");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

    ui->ok->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                          "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");


    connect(ui->ok, SIGNAL(clicked()), SLOT(cancelOnOk()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::setText(QString msg, int value)
{
    setWindowTitle(msg);
    ui->score->setText(msg + "\nYour score: " + QString::number(value));
}

void GameOver::cancelOnOk()
{
    QApplication::exit();
}
