#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver),
    m_filePath("../TowerDefense/bestScores.txt")
{
    ui->setupUi(this);
    this->setFixedSize(410, 500);

    // this will initialize scores vector from file
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
    m_score = value;
    setWindowTitle(msg);

    if (m_scores.back().second < value || m_scores.size() < 10) {
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
    ui->highScores->clear();
    QString input = ui->nameInput->text();
    if (input.size() > 9 || input.size() < 3) {
        ui->highScores->setText("Name must be between 3 and 8 characters long!\nTry again!");
        return ;
    }

    auto numOfSpaces = input.count(' ');
    if (numOfSpaces > 0) {
        ui->highScores->setText("Name cannot contain spaces!\nTry again!");
        return ;
    }

    QPair<QString, int> newScore{input, m_score};

    if (m_scores.size() < 10) {
        m_scores.push_back(newScore);
    } else {
        m_scores.back() = newScore;
    }

    std::sort(m_scores.begin(), m_scores.end(),
              [] (QPair<QString, int> x, QPair<QString, int> y) {return x.second > y.second;});

    displayScores();
    writeScores();

    ui->subScore->setDisabled(true);
    ui->nameInput->setReadOnly(true);
}

void GameOver::readScores()
{
    QFile file(m_filePath.absolutePath());
    file.open(QIODevice::ReadOnly);

    if (! file.isOpen()) {
//        qDebug() << "Opening of the file for reading failed";
        return ;
    }

    QTextStream input(&file);

    QString name;
    int score;
    // we are keeping just the top 10 scores here
    for (int i = 0; i < 10; ++i) {
    // if there are less then ten, we break
        if (input.atEnd())
            break;

        input >> name;

        if (name == "")
            break;

        input >> score;

        m_scores.push_back({name, score});
    }

    file.close();
}

void GameOver::writeScores()
{
    QFile file(m_filePath.absolutePath());
    file.open(QIODevice::WriteOnly);

    if (! file.isOpen()) {
//        qDebug() << "Opening for writing Failed";
        ui->highScores->setText("Unable to load scores...");
        return ;
    }

    QTextStream output(&file);
    for (int i = 0; i < m_scores.size(); ++i) {
        output << m_scores[i].first << " " << m_scores[i].second << endl;
    }

    output.flush();
    file.close();
}

void GameOver::displayScores()
{
    ui->highScores->clear();
    for (int i = 0; i < m_scores.size(); ++i) {
        ui->highScores->append(m_scores[i].first + " " + QString::number(m_scores[i].second));
    }
}
