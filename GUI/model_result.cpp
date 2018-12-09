#include "model_result.h"

#include <cmath>

#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>

ModelResult::ModelResult(QWidget* parent)
    : QDialog(parent)
{
    m_table_widget = new QTableWidget;
    m_table_widget->setRowCount(4);
    m_table_widget->setColumnCount(3);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(pow(i, j+1)));
            m_table_widget->setItem(i, j, item);
        }
    }

    for (int i = 0; i < 3; ++i)
        m_table_widget->setHorizontalHeaderItem(i, new QTableWidgetItem(tr("Product %1").arg(i + 1)));

    m_table_widget->setVerticalHeaderItem(0, new QTableWidgetItem(tr("Prices")));
    m_table_widget->setVerticalHeaderItem(1, new QTableWidgetItem(tr("Quantities")));
    m_table_widget->setVerticalHeaderItem(2, new QTableWidgetItem(tr("Profits")));
    m_table_widget->setVerticalHeaderItem(3, new QTableWidgetItem(tr("Consumer Welfare")));

    m_table_widget->horizontalHeader()->setStretchLastSection(true);
    m_table_widget->verticalHeader()->setStretchLastSection(true);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_table_widget);

    setLayout(layout);
}