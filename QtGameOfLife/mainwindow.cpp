#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGrid();
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
        }
}

void MainWindow::on_startButton_clicked(bool checked){
    if (checked == 1) {
        ui->startButton->setText("Pause");
    }
    else {
        ui->startButton->setText("Start");
    }
}

void MainWindow::on_stepButton_clicked(){
    gameBoard.makeTurn();
    colourCells();
}
