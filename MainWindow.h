#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class YMainWindowClass; };
QT_END_NAMESPACE

class YMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    YMainWindow(QWidget *parent = nullptr);
    ~YMainWindow();

private:
    Ui::YMainWindowClass *ui;
};
