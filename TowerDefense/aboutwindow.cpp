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
    ui->info->setTabText(3, "How to play");

    // disable writing into text edit widgets
    ui->watchTowerText->setReadOnly(true);
    ui->arrowTowerText->setReadOnly(true);
    ui->iceTowerText->setReadOnly(true);
    ui->witchTowerText->setReadOnly(true);
    ui->mageTowerText->setReadOnly(true);

    ui->level1Waves->setReadOnly(true);
    ui->level2Waves->setReadOnly(true);
    ui->level3Waves->setReadOnly(true);

    ui->goblinEdit->setReadOnly(true);
    ui->commonKnightEdit->setReadOnly(true);
    ui->darkKnightEdit->setReadOnly(true);
    ui->zombieDinoEdit->setReadOnly(true);
    ui->mothEdit->setReadOnly(true);
    ui->dragonEdit->setReadOnly(true);
    ui->zombieDragonEdit->setReadOnly(true);

    // set backgrounds on tabs
    ui->towers->setStyleSheet("background-color: rgb(75, 75, 70);");
    ui->enemies->setStyleSheet("background-color: rgb(75, 75, 70);");
    ui->levels->setStyleSheet("background-image: url(:/images/wallStore.jpg)");
    ui->HowToPlay->setStyleSheet("background-image: url(:/images/wallStore.jpg)");
    //ui->info->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->info->setStyleSheet("background-color: rgb(184,134,11);");

    // set backgrounds on widgets in 'enemies' tab
    ui->goblinEdit->setStyleSheet("border-image: url(:/images/wallStore.jpg);");
    ui->commonKnightEdit->setStyleSheet("border-image: url(:/images/wallStore.jpg);");
    ui->darkKnightEdit->setStyleSheet("border-image: url(:/images/wallStore.jpg);");
    ui->zombieDinoEdit->setStyleSheet("border-image: url(:/images/wallStore.jpg);");
    ui->mothEdit->setStyleSheet("background-image: url(:/images/wallStoreGrey.jpg);");
    ui->dragonEdit->setStyleSheet("background-image: url(:/images/wallStoreGrey.jpg);");
    ui->zombieDragonEdit->setStyleSheet("background-image: url(:/images/wallStoreGrey.jpg);");

    // set backgrounds on widgets in 'towers' tab
    ui->watchTowerText->setStyleSheet("background-image: url(:/images/wallStore.jpg);");
    ui->arrowTowerText->setStyleSheet("background-image: url(:/images/wallStore.jpg);");
    ui->iceTowerText->setStyleSheet("background-image: url(:/images/wallStoreGrey.jpg);");
    ui->witchTowerText->setStyleSheet("background-image: url(:/images/wallStoreGrey.jpg);");
    ui->mageTowerText->setStyleSheet("background-image: url(:/images/wallStoreFire.jpg);");
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
