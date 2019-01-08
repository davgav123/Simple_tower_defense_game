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
    void submitScore();

private:
    Ui::GameOver *ui;

    QVector<QPair<QString, int>> m_scores;
    int m_score;
    QDir m_filePath;

    void readScores();
    void writeScores();
    void displayScores();
};

#endif // GAMEOVER_H
