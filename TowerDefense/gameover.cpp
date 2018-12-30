#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
//    setWindowTitle("Game over!");
    this->setFixedSize(400, 200);
    QPixmap backgroundImg(":/images/map.jpg");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

    ui->exit->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->newGame->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                               "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    connect(ui->exit, SIGNAL(clicked()), SLOT(exitOnClick()));
    connect(ui->newGame, SIGNAL(clicked()), SLOT(startNewGame()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::setText(QString msg, int value)
{
    setWindowTitle(msg);
    ui->score->setFont(QFont("sans serif", 20, QFont::StyleItalic, true));
    ui->score->setText(msg + "\nYour score: " + QString::number(value));
}

void GameOver::exitOnClick()
{
    QApplication::exit();
}

void GameOver::startNewGame()
{
    StartWindow *sw = new StartWindow();
    sw->show();

    delete this;
}
