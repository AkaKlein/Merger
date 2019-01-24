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

    // Add a "Model" menu to be able to select the type of model that will be loaded.
    QMenu* model_menu = menuBar()->addMenu(tr("&Model"));
    model_menu->addSeparator()->setText(tr("Model type"));
    
    // Create an action inside the model menu for each model type.
    QActionGroup* model_type_group = new QActionGroup(this);
    for (int i = 0; i < static_cast<int>(ModelType::Count); ++i)
    {
        ModelType model_type = static_cast<ModelType>(i);
        QString action_text = QString::fromStdString(ModelTypeToExtendedString(model_type));
        QAction* action = model_menu->addAction(action_text, [this, model_type]() { m_selected_model_type = model_type; });
        
        // Mark it as checkable and add it to the group of types, so that only one can be checked at the same time.
        action->setCheckable(true);
        model_type_group->addAction(action);

        // The default model will be Linear Demands with Constant Costs.
        if (model_type == ModelType::LinearDemandsConstantCosts)
        {
            action->setChecked(true);
            m_selected_model_type = model_type;
        }
    }

    // Open a new model window every time the user loads a file.
    connect(m_load_model_widget, &LoadModelWidget::LoadData, this, &MainWindow::LoadModel);

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
