#include "compare_table_view.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>

#include "compare_table_data.h"

CompareTableView::CompareTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model1, std::shared_ptr<ModelInterface>& model2)
    : BaseTableView(parent)
{
    // Create the model and set it to the view.
    m_data = new CompareTableData(model1, model2);
    setModel(m_data);

    // Make it visible.
    show();
}