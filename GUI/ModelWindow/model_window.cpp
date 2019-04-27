#include "model_window.h"

#include <iostream>

#include <QApplication>
#include <QMenuBar>
#include <QVBoxLayout>

#include "GUI/CompareDialog/compare_table_view.h"
#include "GUI/ModelWindow/MergeDialog/merge_dialog.h"
#include "GUI/PlotDialog/plot_dialog.h"

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

    // Notify the other models about this model.
    for (auto it = m_model_windows.begin(); it != m_model_windows.end(); ++it)
    {
        if (*it != this)
            (*it)->ReportModelCreated(m_model_index, static_cast<ModelTableData*>(m_model_table_view->model())->GetModel().Clone());
    }

    show();
    activateWindow();
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

    // Notify the other models about this model.
    for (auto it = m_model_windows.begin(); it != m_model_windows.end(); ++it)
    {
        if (*it != this)
            (*it)->ReportModelCreated(m_model_index, static_cast<ModelTableData*>(m_model_table_view->model())->GetModel().Clone());
    }

    show();
    activateWindow();
}

void ModelWindow::ReportModelCreated(int id, std::shared_ptr<ModelInterface> const& model)
{
    for (PlotDialog* plot_dialog : m_plot_dialogs)
        plot_dialog->AddModel(id, model);
}

void ModelWindow::ReportModelDeleted(int id)
{
    m_compare_menu->removeAction(m_compare_actions[id]);
    for (PlotDialog* plot_dialog : m_plot_dialogs)
        plot_dialog->RemoveModel(id);
}

void ModelWindow::MergeClicked()
{
    MergeDialog* merge_dialog = new MergeDialog(this, static_cast<ModelTableData*>(m_model_table_view->model())->GetModel());
    connect(merge_dialog, &MergeDialog::ApplyButtonClicked, 
            [this](std::shared_ptr<ModelInterface> model) { emit CreateNewModelWindow(model); });
}

void ModelWindow::PlotClicked()
{
    ModelInterface const& model = static_cast<ModelTableData*>(m_model_table_view->model())->GetModel();
    PlotDialog* plot_dialog = new PlotDialog(this, m_model_index, model);
    
    for (ModelWindow* model_window : m_model_windows)
    {
        auto other_model = static_cast<ModelTableData*>(model_window->m_model_table_view->model())->GetModel().Clone();
        if (this != model_window)
            plot_dialog->AddModel(model_window->GetModelIndex(), other_model);
    }

    m_plot_dialogs.push_back(plot_dialog);

    connect(plot_dialog, &QDialog::finished, [this, plot_dialog]() 
    { 
        for (auto it = m_plot_dialogs.begin(); it != m_plot_dialogs.end(); ++it)
        {
            if (*it == plot_dialog)
            {
                m_plot_dialogs.erase(it);
                return;
            }
        }
    });
}

void ModelWindow::CompareClicked(int model_index)
{
    QDialog* compare_dialog = new QDialog(this);

    // Get the model of this window.
    std::shared_ptr<ModelInterface> model1 = static_cast<ModelTableData*>(m_model_table_view->model())->GetModel().Clone();

    // Get the other model.
    std::shared_ptr<ModelInterface> model2;
    for (std::size_t i = 0; i < m_model_windows.size(); ++i)
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

    // Add a "Plot" action.
    menuBar()->addAction(tr("&Plot"), this, &ModelWindow::PlotClicked);

    // Add a "Compare" menu.
    m_compare_menu = menuBar()->addMenu(tr("&Compare"));
    for (ModelWindow* model_window : m_model_windows)
        AddCompareAction(model_window->m_model_index);

    m_model_windows.push_back(this);

    // Add a compare action for this model in every model window.
    for (ModelWindow* model_window : m_model_windows)
        model_window->AddCompareAction(m_model_index);

    // Close all the open children dialogs when this window is closed.
    setAttribute(Qt::WA_DeleteOnClose);
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
            (*it)->ReportModelDeleted(m_model_index);
            ++it;
        }
    }
}