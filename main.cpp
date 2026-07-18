// SPDX-License-Identifier: MIT

#include "Widgets/DABWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YDABWidget w;
    w.show();
    return a.exec();
}
