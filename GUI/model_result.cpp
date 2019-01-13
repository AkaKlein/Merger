#include "model_result.h"

#include <cmath>

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

    for (int i = 0; i < 5; ++i)
    {
        ColumnVector v;

        if (i == 0)
        {
            m_table_widget->setVerticalHeaderItem(0, new QTableWidgetItem(tr("Prices")));
            v = prices;
        }
        else if (i == 1)
        {
            m_table_widget->setVerticalHeaderItem(1, new QTableWidgetItem(tr("Quantities")));
            v = quantities;
        }
        else if (i == 2)
        {
            m_table_widget->setVerticalHeaderItem(2, new QTableWidgetItem(tr("Costs")));
            v = model->ComputeCosts(quantities);
        }
        else if (i == 3)
        {
            m_table_widget->setVerticalHeaderItem(3, new QTableWidgetItem(tr("Profits")));
            v = model->ComputeProfits(prices);
        }
        else
        {
            m_table_widget->setVerticalHeaderItem(4, new QTableWidgetItem(tr("Consumer Welfare")));
            v = model->ComputeConsumerWelfare(prices);
        }

        for (int j = 0; j < model->GetNumberOfProducts(); ++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(v[j]));
            m_table_widget->setItem(i, j, item);
        }
    }

    for (int i = 0; i < 3; ++i)
        m_table_widget->setHorizontalHeaderItem(i, new QTableWidgetItem(tr("Product %1").arg(i + 1)));

    m_table_widget->horizontalHeader()->setStretchLastSection(true);
    m_table_widget->verticalHeader()->setStretchLastSection(true);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_table_widget);

    setLayout(layout);
}