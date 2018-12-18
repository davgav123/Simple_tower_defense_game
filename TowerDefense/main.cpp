#include "tower.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Game g;
    g.show();

    return app.exec();
}
