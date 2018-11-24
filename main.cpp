#include <QtWidgets>

#include "GUI/main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
