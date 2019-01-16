#include "model_result.h"

#include <cmath>

#include <QApplication>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>

ModelResult::ModelResult(QWidget* parent, std::unique_ptr<ModelInterface> model, int model_index)
    : QDialog(parent)
{
    setWindowTitle(QString::fromStdString("Model " + std::to_string(model_index) + " [" + model->GetName() + "]"));

    m_table_widget = new QTableWidget;
    m_table_widget->setRowCount(5);
    m_table_widget->setColumnCount(model->GetNumberOfProducts());

    ColumnVector prices = model->ComputePrices();
    ColumnVector quantities = model->ComputeQuantities(prices);

    PopulateRow(0, tr("Prices"), prices);
    PopulateRow(1, tr("Quantities"), quantities);
    PopulateRow(2, tr("Costs"), model->ComputeCosts(quantities));
    PopulateRow(3, tr("Profits"), model->ComputeProfits(prices));
    PopulateRow(4, tr("Consumer Welfare"), model->ComputeConsumerWelfare(prices));

    for (int i = 0; i < model->GetNumberOfProducts(); ++i)
        m_table_widget->setHorizontalHeaderItem(i, new QTableWidgetItem(tr("Product %1").arg(i + 1)));

    m_table_widget->horizontalHeader()->setStretchLastSection(true);
    m_table_widget->verticalHeader()->setStretchLastSection(true);


    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_table_widget);

    setLayout(layout);

    QApplication::processEvents();
    AdjustTableSize();
}

void ModelResult::PopulateRow(int index, QString const& name, ColumnVector const& values)
{
    m_table_widget->setVerticalHeaderItem(index, new QTableWidgetItem(name));
    for (int i = 0; i < m_table_widget->rowCount(); ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(values[i]));
        m_table_widget->setItem(index, i, item);
    }
}

void ModelResult::AdjustTableSize()
{
    m_table_widget->resizeColumnsToContents();
    m_table_widget->resizeRowsToContents();

    QRect rect = m_table_widget->geometry();
    
    int width = 30 + m_table_widget->verticalHeader()->width();
    for (int i = 0; i < m_table_widget->columnCount(); ++i)
        width += m_table_widget->columnWidth(i);
    rect.setWidth(width);

    int height = 10 + m_table_widget->horizontalHeader()->height();
    for (int i = 0; i < m_table_widget->rowCount(); ++i)
        height += m_table_widget->rowHeight(i);
    rect.setHeight(height);

    m_table_widget->setMinimumSize(std::min(width, 1000), height);
}