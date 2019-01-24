#include "model_window.h"

#include <iostream>

#include <QApplication>
#include <QMenuBar>

#include "GUI/ModelWindow/MergeDialog/merge_dialog.h"

#include "model_table_data.h"
#include "model_table_view.h"

ModelWindow::ModelWindow(
    QWidget* parent, 
    std::string const& file_path, 
    ModelType model_type, 
    int model_index,
    std::vector<ModelWindow*>& model_windows)
    :
    QMainWindow(parent),
    m_model_windows(model_windows)
{
    Initialize(model_type, model_index);

    // Add a widget to show the model results.
    m_model_table_view = new ModelTableView(this, file_path, model_type);
    setCentralWidget(m_model_table_view);

    show();
}

ModelWindow::ModelWindow(
    QWidget* parent, 
    std::shared_ptr<ModelInterface>& model, 
    int model_index,
    std::vector<ModelWindow*>& model_windows)
    :
    QMainWindow(parent),
    m_model_windows(model_windows)
{
    Initialize(model->GetType(), model_index);

    // Add a widget to show the model results.
    m_model_table_view = new ModelTableView(this, model);
    setCentralWidget(m_model_table_view);

    show();
}

void ModelWindow::MergeClicked()
{
    MergeDialog* merge_dialog = new MergeDialog(this, static_cast<ModelTableData*>(m_model_table_view->model())->GetModel());
    connect(merge_dialog, &MergeDialog::ApplyButtonClicked, 
            [this](std::shared_ptr<ModelInterface> model) { emit CreateNewModelWindow(model); });
}

void ModelWindow::Initialize(ModelType model_type, int model_index)
{
    // Set the title of the window.
    std::string title = "Model " + std::to_string(model_index) + " [" + ModelTypeToExtendedString(model_type) + "]";
    setWindowTitle(QString::fromStdString(title));

    // Add a "Merge" action.
    menuBar()->addAction(tr("&Merge"), this, &ModelWindow::MergeClicked);

    // Add itself to the vector of model windows.
    m_model_windows.push_back(this);
}

void ModelWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);

    // Remove itself from the vector of model windows.
    for (auto it = m_model_windows.begin(); it != m_model_windows.end(); ++it)
    {
        if (*it == this)
        {
            m_model_windows.erase(it);
            return;
        }
    }
}