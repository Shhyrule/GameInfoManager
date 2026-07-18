// SPDX-License-Identifier: MIT

#include "MainWindow.h"

YMainWindow::YMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YMainWindowClass())
{
    ui->setupUi(this);
}

YMainWindow::~YMainWindow()
{
    delete ui;
}
