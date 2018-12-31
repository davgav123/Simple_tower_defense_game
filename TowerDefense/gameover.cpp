#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
//    setWindowTitle("Game over!");
    this->setFixedSize(410, 400);
    QPixmap backgroundImg(":/images/map.jpg");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

    // setup components
    ui->highScores->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->highScores->setReadOnly(true);
    ui->score->setFont(QFont("sans serif", 20, QFont::StyleItalic, true));

    ui->exit->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->newGame->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                               "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    connect(ui->exit, SIGNAL(clicked()), SLOT(exitOnClick()));
    connect(ui->newGame, SIGNAL(clicked()), SLOT(startNewGame()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::setText(QString msg, int value)
{
    setWindowTitle(msg);

    QVector<QPair<QString, int>> scores;

    // read file that contains best scores
    QDir fileName("../TowerDefense/bestScores.txt");
    readScores(scores, fileName);

    QPair<QString, int> newScore{"user", value};
    if (scores.size() < 10) {
        ui->score->setText(msg + "\nYour score: " + QString::number(value) +
                                   "\n You are in the top ten!");
        scores.push_back(newScore);
    } else if (value > scores.back().second) {
        ui->score->setText(msg + "\nYour score: " + QString::number(value) +
                                   "\n You are in the top ten!");
        scores.back() = newScore;
    } else {
        ui->score->setText(msg + "\nYour score: " + QString::number(value));
    }

    // sort by scores
    std::sort(scores.begin(), scores.end(),
              [] (QPair<QString, int> x, QPair<QString, int> y) {return x.second > y.second;});

    // write scores on the screen and in file
    writeScores(scores, fileName);
}

void GameOver::exitOnClick()
{
    QApplication::exit();
}

void GameOver::startNewGame()
{
    QApplication::quit();
    QProcess::startDetached(QApplication::arguments()[0], QApplication::arguments());

    delete this;
}

void GameOver::readScores(QVector<QPair<QString, int> > &scores, QDir path)
{
    QFile file(path.absolutePath());
    file.open(QIODevice::ReadOnly);

    if (! file.isOpen()) {
        qDebug() << "Opening of the file for reading failed";
        return ;
    }

    QTextStream input(&file);

    QString name;
    int score;
    // we are keeping just top 10 scores here
    for (int i = 0; i < 10; ++i) {
    // if there are less then ten, we break
        if (input.atEnd())
            break;

        input >> name;

        if (name == "")
            break;

        input >> score;

        scores.push_back({name, score});
    }
    file.close();
}

void GameOver::writeScores(const QVector<QPair<QString, int> > &scores, QDir path)
{
    QFile file(path.absolutePath());
    file.open(QIODevice::WriteOnly);

    if (! file.isOpen()) {
        qDebug() << "Opening for writing Failed";
        ui->highScores->setText("Unable to load scores...");
        return ;
    }

    QTextStream output(&file);

    ui->highScores->clear();
    for (int i = 0; i < scores.size(); ++i) {
        // add to UI
        ui->highScores->append(scores[i].first + " " + QString::number(scores[i].second));
        // add to file
        output << scores[i].first << " " << scores[i].second << endl;
    }
    output.flush();
    file.close();
}
