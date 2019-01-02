#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "game.h"
#include "aboutwindow.h"
#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include <QMediaPlaylist>
#include <QMediaPlayer>

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
    void startLevelOne();
    void startLevelTwo();
    void startLevelThree();
    void showAboutWindow();
    void quitGame();

private:
    Ui::StartWindow *ui;
    QMediaPlayer *music;

    AboutWindow *m_about;
};

#endif // STARTWINDOW_H
