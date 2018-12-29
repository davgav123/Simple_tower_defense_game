#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QString>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    ~GameOver();

    void setText(QString msg, int value);

private slots:
    void cancelOnOk();

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
