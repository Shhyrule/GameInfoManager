// SPDX-License-Identifier: MIT

#include "Widgets/MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YMainWindow w;
    w.show();
    return a.exec();
}
