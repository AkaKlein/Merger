#include "model_window.h"

#include <iostream>

#include <QApplication>

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
    // Set the title of the window.
    std::string title = "Model " + std::to_string(model_index) + " [" + ModelTypeToExtendedString(model_type) + "]";
    setWindowTitle(QString::fromStdString(title));

    // Add a widget to show the model results.
    m_model_table_view = new ModelTableView(this, file_path, model_type);
    setCentralWidget(m_model_table_view);

    // Add itself to the vector of model windows.
    m_model_windows.push_back(this);

    // Make the window visible.
    show();
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