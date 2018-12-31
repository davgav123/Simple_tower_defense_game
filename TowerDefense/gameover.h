#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QString>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QPair>
#include <QDir>
#include <algorithm>

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
    void exitOnClick();
    void startNewGame();

private:
    Ui::GameOver *ui;

    void readScores(QVector<QPair<QString, int>> & scores, QDir path);
    void writeScores(const QVector<QPair<QString, int>> & scores, QDir path);
};

#endif // GAMEOVER_H
