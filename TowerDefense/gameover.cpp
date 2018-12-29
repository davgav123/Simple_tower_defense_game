#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);

    connect(ui->ok, SIGNAL(clicked()), SLOT(cancelOnOk()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::setText(QString msg, int value)
{
    setWindowTitle(msg);
    ui->score->setText(msg + " Score: " + QString::number(value));
}

void GameOver::cancelOnOk()
{
    QApplication::exit();
}
