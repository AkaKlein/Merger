#include "main_window.h"

#include <QActionGroup>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow()
{
    // Add the menus
    QMenu* file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(tr("E&xit"), []() { QApplication::quit(); });

    QMenu* model_menu = menuBar()->addMenu(tr("&Model"));

    model_menu->addSeparator()->setText(tr("Model type"));
    
    QAction* ldwcc = model_menu->addAction("Linear demands with constant costs");
    ldwcc->setCheckable(true);

    QAction* ldwlc = model_menu->addAction("Linear demands with linear costs");
    ldwlc->setCheckable(true);

    QActionGroup* model_type_group = new QActionGroup(this);
    model_type_group->addAction(ldwcc);
    model_type_group->addAction(ldwlc);
    ldwcc->setChecked(true);


    // Add the model widget
    m_model_widget = new ModelWidget;
    setCentralWidget(m_model_widget);
}
