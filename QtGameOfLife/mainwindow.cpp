#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>
#include<cstring>
#include<fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    setupGrid();
    colourCells();

    generationLabel = new QLabel (this);
    updateGeneration();
    ui->horizontalLayout_2->addWidget(generationLabel);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (handleStart()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT (saveToFile()));
    connect(ui->loadButton, SIGNAL(clicked(bool)), this, SLOT (loadToFile()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::colourCell (int i, int j, bool isAlive){
    QPalette p(buttons[i][j]->palette());

    p.setColor(QPalette::Button, QColor(isAlive ? "#ffd500" : "#767676"));
    buttons[i][j]->setPalette(p);
}

void MainWindow::colourCells (){
    for (int i = 0; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++)
            colourCell (i, j, gameBoard.getState(i, j));
}

void MainWindow::updateGeneration (){
    std::string tempString = "Generation: " + std::to_string (gameBoard.generationNumber)
            + " Population: " + std::to_string(gameBoard.populationNumber);

    generationLabel->setText(QString::fromStdString(tempString));
}

void MainWindow::setupGrid(){
    ui->gridLayout->setHorizontalSpacing(0);
    ui->gridLayout->setVerticalSpacing(0);
    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setAlignment(Qt::AlignHCenter);

    for (int i = 0 ; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++){
            buttons[i][j] = new QPushButton ();
            ui->gridLayout->addWidget(buttons[i][j], i, j);
            connect(this->buttons[i][j], &QPushButton::clicked, [=]{
                handleButton(i, j);
            });
        }
}

void MainWindow::handleStart(){
    on_stepButton_clicked();
}

void MainWindow::handleButton(int i, int j){
    gameBoard.change(i, j);
    colourCell(i, j, gameBoard.getState(i, j));
    updateGeneration();
}

void MainWindow::on_startButton_clicked(bool checked){
    ui->startButton->setText(checked ? "Pause" : "Start");

    if (checked) timer->start(250);
    else timer->stop();
}

void MainWindow::on_stepButton_clicked(){
    gameBoard.makeTurn();
    colourCells();
    updateGeneration();
}

void MainWindow::on_clearButton_clicked(){
    gameBoard.clear();
    colourCells();
    updateGeneration();
}

void MainWindow::saveToFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Game of Life state"), "",
            tr("Game of Life state (*.gl);;All Files (*)"));

    if (fileName.isEmpty()) return;

    std::ofstream savedState;
    savedState.open (fileName.toUtf8().constData(), std::ofstream::out);

    for (int i = 0; i < TableSize; i++){
        for (int j = 0; j < TableSize; j++){
            if (gameBoard.getState(i, j) == 1) savedState << "#";
            else savedState << ".";
        }

        savedState << "\n";
    }

    savedState.close ();
}

void MainWindow::loadToFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Game of Life state"), "",
            tr("Game of Life state (*.gl);;All Files (*)"));

    if (fileName.isEmpty()) return;

    std::ifstream savedState;
    savedState.open(fileName.toUtf8().constData(), std::ifstream::in);

    on_clearButton_clicked();

    for (int i = 0; i < TableSize; i++){
        for (int j = 0; j < TableSize; j++)
            if (savedState.get() == '#') gameBoard.change(i, j);
        savedState.get();
    }

    colourCells();
    updateGeneration();
    savedState.close();
}
