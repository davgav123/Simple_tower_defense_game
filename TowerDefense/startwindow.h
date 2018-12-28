#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "game.h"
#include <QMainWindow>
#include <QPalette>
#include <QPixmap>

namespace Ui {
class StartWindow;
}

extern Game *g;

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void startLevelOne() const;
    void startLevelTwo() const;
    void startLevelThree() const;
    void quitGame();

private:
    Ui::StartWindow *ui;
    QMediaPlayer *music;
};

#endif // STARTWINDOW_H
