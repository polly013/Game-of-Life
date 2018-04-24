#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGrid();
    colourCells();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (handleStart()));

    timer->start(250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::colourCell (int i, int j, bool isLive){
    QPalette p(buttons[i][j]->palette());

    p.setColor(QPalette::Button, QColor(isLive ? "#ffd500" : "#767676"));
    buttons[i][j]->setPalette(p);
}

void MainWindow::colourCells (){
    for (int i = 0; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++)
            colourCell (i, j, gameBoard.state(i, j));
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
    if (gameOn) on_stepButton_clicked();
}

void MainWindow::handleButton(int i, int j){
    gameBoard.change(i, j);
    colourCell(i, j, gameBoard.state(i, j));
}

void MainWindow::on_startButton_clicked(bool checked){
    ui->startButton->setText(checked ? "Pause" : "Start");

    if (checked) gameOn = true;
    else gameOn = false;
}

void MainWindow::on_stepButton_clicked(){
    gameBoard.makeTurn();
    colourCells ();
}

void MainWindow::on_clearButton_clicked()
{
    gameBoard.clear();
    colourCells ();
}
