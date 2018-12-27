#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "game.h"
#include <QMainWindow>

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
    void quitGame();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H