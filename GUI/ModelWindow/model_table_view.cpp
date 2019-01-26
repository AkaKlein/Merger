#include "model_table_view.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>

#include "model_table_data.h"

ModelTableView::ModelTableView(QWidget* parent, std::string const& file_path, ModelType model_type)
    : BaseTableView(parent)
{
    // Create the model and set it to the view.
    m_data = new ModelTableData(file_path, model_type);
    setModel(m_data);

    // Make it visible.
    show();
}

ModelTableView::ModelTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model)
    : BaseTableView(parent)
{
    // Create the model and set it to the view.
    m_data = new ModelTableData(model);
    setModel(m_data);

    // Make it visible.
    show();
}