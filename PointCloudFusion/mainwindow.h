﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zPCFWidget.h"

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
    void on_readFile_action_triggered();

private:
    Ui::MainWindow *ui;
//    zPCFWidget *pcfWidget;
};

#endif // MAINWINDOW_H
