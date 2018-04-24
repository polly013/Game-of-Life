#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QTimer>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked (bool checked);
    void on_stepButton_clicked ();
    void on_clearButton_clicked ();
    void handleButton (int i, int j);
    void handleStart ();

signals:
    void clicked (bool checked);

private:
    bool gameOn;
    Ui::MainWindow *ui;
    QPushButton *buttons[TableSize][TableSize];
    QTimer *timer;
    Board gameBoard;
    void setupGrid ();
    void colourCells ();
    void colourCell (int i, int j, bool isLive);
};

#endif // MAINWINDOW_H
