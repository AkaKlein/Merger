#include "base_table_view.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>

void BaseTableView::keyPressEvent(QKeyEvent* event)
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

QSize BaseTableView::sizeHint() const
{    
    int width = 2 * frameWidth() + verticalHeader()->width();
    for (int i = 0; i < model()->columnCount(); ++i)
        width += columnWidth(i);

    int height = 2 * frameWidth() + horizontalHeader()->height();
    for (int i = 0; i < model()->rowCount(); ++i)
        height += rowHeight(i);

    return QSize(width, height);
}