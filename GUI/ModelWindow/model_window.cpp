#include "model_window.h"

#include <iostream>

#include <QApplication>
#include <QMenuBar>
#include <QVBoxLayout>

#include "GUI/CompareDialog/compare_table_view.h"
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
    m_model_index(model_index),
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
    m_model_index(model_index),
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

void ModelWindow::CompareClicked(int model_index)
{
    QDialog* compare_dialog = new QDialog(this);

    // Get the model of this window.
    std::shared_ptr<ModelInterface> model1 = static_cast<ModelTableData*>(m_model_table_view->model())->GetModel().Clone();

    // Get the other model.
    std::shared_ptr<ModelInterface> model2;
    for (int i = 0; i < m_model_windows.size(); ++i)
    {
        if (m_model_windows[i]->m_model_index == model_index)
        {
            model2 = static_cast<ModelTableData*>(m_model_windows[i]->m_model_table_view->model())->GetModel().Clone();
            break;
        }
    }

    // Create the dialog
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new CompareTableView(compare_dialog, model1, model2));
    compare_dialog->setLayout(layout);
    compare_dialog->setWindowTitle(tr("Compare Model %1 and Model %2").arg(m_model_index).arg(model_index));

    compare_dialog->show();
}

void ModelWindow::Initialize(ModelType model_type, int model_index)
{
    // Set the title of the window.
    std::string title = "Model " + std::to_string(model_index) + " [" + ModelTypeToExtendedString(model_type) + "]";
    setWindowTitle(QString::fromStdString(title));

    // Add a "Merge" action.
    menuBar()->addAction(tr("&Merge"), this, &ModelWindow::MergeClicked);

    // Add a "Compare" menu.
    m_compare_menu = menuBar()->addMenu(tr("&Compare"));
    for (ModelWindow* model_window : m_model_windows)
        AddCompareAction(model_window->m_model_index);

    m_model_windows.push_back(this);

    // Add a compare action for this model in every model window.
    for (ModelWindow* model_window : m_model_windows)
        model_window->AddCompareAction(m_model_index);
}

void ModelWindow::AddCompareAction(int model_index)
{
    m_compare_actions[model_index] = m_compare_menu->addAction(tr("Model %1").arg(model_index), 
                                                                  [this, model_index]() { CompareClicked(model_index); });
}

void ModelWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);

    // Remove itself from the vector of model windows.
    for (auto it = m_model_windows.begin(); it != m_model_windows.end();)
    {
        if (*it == this)
            it = m_model_windows.erase(it);
        else
        {
            (*it)->m_compare_menu->removeAction((*it)->m_compare_actions[m_model_index]);
            ++it;
        }
    }
}