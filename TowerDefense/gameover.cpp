#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver),
    filePath("../TowerDefense/bestScores.txt")
{
    ui->setupUi(this);
    this->setFixedSize(410, 500);

    // this will init scores vector from file
    readScores();

    // set background
    QPixmap backgroundImg(":/images/map.jpg");
    backgroundImg = backgroundImg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImg);
    setPalette(palette);

    // setup components
    ui->highScores->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->highScores->setReadOnly(true);
    ui->highScores->setStyleSheet("background-image: url(:/images/scoresBackground.png)");
    ui->highScores->setFont(QFont("sans serif", 13, QFont::StyleItalic, true));

    ui->exit->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                            "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->newGame->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                               "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->score->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->score->setFont(QFont("sans serif", 20, QFont::StyleItalic, true));

    ui->nameInput->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->nameInput->setReadOnly(true);
    ui->nameInput->setStyleSheet("background-color: orange");

    ui->subScore->setDisabled(true);
    ui->subScore->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                                "color: rgb(57, 19, 19); font-weight: bold; font-size: 20px; font-style: italic;}");

    // add click actions to buttons
    connect(ui->exit, SIGNAL(clicked()), SLOT(exitOnClick()));
    connect(ui->newGame, SIGNAL(clicked()), SLOT(startNewGame()));
    connect(ui->subScore, SIGNAL(clicked()), SLOT(submitScore()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::setText(QString msg, int value)
{
    score = value;
    setWindowTitle(msg);

    if (scores.back().second < value || scores.size() < 10) {
        ui->score->setText(msg + "\nYour score: " + QString::number(value) +
                                   "\nYou are in the top ten!");
        ui->subScore->setDisabled(false);
        ui->nameInput->setReadOnly(false);
    } else {
        ui->score->setText(msg + "\nYour score: " + QString::number(value));
    }

    displayScores();
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

void GameOver::submitScore()
{
    qDebug() << "Name and score are submited";

    ui->highScores->clear();
    QString input = ui->nameInput->text();
    if (input.size() > 9 || input.size() < 3) {
        ui->highScores->setText("Name must be between 3 and 8 characters long");
        return ;
    }

    QPair<QString, int> newScore{input, score};

    if (scores.size() < 10) {
        scores.push_back(newScore);
    } else {
        scores.back() = newScore;
    }

    std::sort(scores.begin(), scores.end(),
              [] (QPair<QString, int> x, QPair<QString, int> y) {return x.second > y.second;});

    displayScores();
    writeScores();

    ui->subScore->setDisabled(true);
    ui->nameInput->setReadOnly(true);
}

void GameOver::readScores()
{
    QFile file(filePath.absolutePath());
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

void GameOver::writeScores()
{
    QFile file(filePath.absolutePath()); // <- ove sam stavio atribut
    file.open(QIODevice::WriteOnly);

    if (! file.isOpen()) {
        qDebug() << "Opening for writing Failed";
        ui->highScores->setText("Unable to load scores...");
        return ;
    }

    QTextStream output(&file);
    for (int i = 0; i < scores.size(); ++i) {
        output << scores[i].first << " " << scores[i].second << endl;
    }
    output.flush();
    file.close();
}

void GameOver::displayScores()
{
    ui->highScores->clear();
    for (int i = 0; i < scores.size(); ++i) {
        ui->highScores->append(scores[i].first + " " + QString::number(scores[i].second));
    }
}
