#include "startwindow.h"
#include "tower.h"
#include "game.h"

#include <QApplication>

Game *g;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // start window
    StartWindow startWindow;
    startWindow.show();

//    g = new Game();
//    g->show();

    return app.exec();
}

