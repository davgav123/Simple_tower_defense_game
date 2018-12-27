#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

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
