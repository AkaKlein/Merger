#include "main_window.h"

#include <QActionGroup>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

#include "GUI/ModelWindow/model_window.h"
#include "Models/model_interface.h"

#include "load_model_widget.h"

class ModelInterface;

MainWindow::MainWindow()
{
    // Add the load model widget.
    m_load_model_widget = new LoadModelWidget;
    setCentralWidget(m_load_model_widget);

    // Add a "File" menu with an exit action.
    QMenu* file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(tr("E&xit"), []() { QApplication::quit(); });

    // Open a new model window every time the user loads a file.
    connect(m_load_model_widget, &LoadModelWidget::LoadData, this, &MainWindow::LoadModel);

    // Handle the changes of model types.
    connect(m_load_model_widget, &LoadModelWidget::ModelTypeChanged, [this](ModelType type) { m_selected_model_type = type; });

    // Make the window visible.
    show();
}

void MainWindow::LoadModel(std::string const& file_path)
{
    ModelWindow* model_window = new ModelWindow(this, file_path, m_selected_model_type, m_model_index++, m_model_windows);
    connect(model_window, &ModelWindow::CreateNewModelWindow, this, &MainWindow::CreateMergerModelWindow);
}

void MainWindow::CreateMergerModelWindow(std::shared_ptr<ModelInterface> model)
{
    ModelWindow* merger_window = new ModelWindow(this, model, m_model_index++, m_model_windows);
    connect(merger_window, &ModelWindow::CreateNewModelWindow, this, &MainWindow::CreateMergerModelWindow);
}
