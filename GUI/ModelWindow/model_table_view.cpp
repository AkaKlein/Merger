#include "model_table_view.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>

#include "model_table_data.h"

ModelTableView::ModelTableView(QWidget* parent, std::string const& file_path, ModelType model_type)
    : QTableView(parent)
{
    // Create the model and set it to the view.
    m_data = new ModelTableData(file_path, model_type);
    setModel(m_data);

    // Make it visible.
    show();
}

ModelTableView::ModelTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model)
    : QTableView(parent)
{
    // Create the model and set it to the view.
    m_data = new ModelTableData(model);
    setModel(m_data);

    // Make it visible.
    show();
}

void ModelTableView::keyPressEvent(QKeyEvent* event)
{
    // Implement copy for multiple cells.
    if (!selectedIndexes().isEmpty() && event->matches(QKeySequence::Copy))
    {
        QString text;
        QItemSelectionRange range = selectionModel()->selection().first();
        for (int i = range.top(); i <= range.bottom(); ++i)
        {
            QStringList rowContents;
            for (int j = range.left(); j <= range.right(); ++j)
                rowContents << model()->index(i,j).data().toString();
            text += rowContents.join("\t");
            text += "\n";
        }
        QApplication::clipboard()->setText(text);
    }

    QTableView::keyPressEvent(event);
}

QSize ModelTableView::sizeHint() const
{    
    int width = 2 * frameWidth() + verticalHeader()->width();
    for (int i = 0; i < model()->columnCount(); ++i)
        width += columnWidth(i);

    int height = 2 * frameWidth() + horizontalHeader()->height();
    for (int i = 0; i < model()->rowCount(); ++i)
        height += rowHeight(i);

    return QSize(width, height);
}