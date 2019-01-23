#include <iostream>

#include <QApplication>

#include "GUI/MainWindow/main_window.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;

    return app.exec();
}
