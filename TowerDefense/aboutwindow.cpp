#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    // set names of the tabs
    ui->info->setTabText(0, "Towers");
    ui->info->setTabText(1, "Levels");
    ui->info->setTabText(2, "Enemies");

    // disable writing into text edit widgets
    ui->watchTowerText->setReadOnly(true);
    ui->arrowTowerText->setReadOnly(true);
    ui->iceTowerText->setReadOnly(true);
    ui->witchTowerText->setReadOnly(true);
    ui->mageTowerText->setReadOnly(true);

    ui->level1Waves->setReadOnly(true);
    ui->level2Waves->setReadOnly(true);
    ui->level3Waves->setReadOnly(true);

    ui->towers->setStyleSheet("background-image: url(:/images/background.png)");
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
