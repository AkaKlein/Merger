#include "firm_widget.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "Models/model_interface.h"

#include "product_list_item.h"

FirmWidget::FirmWidget(QWidget* parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    m_product_list = new QListWidget;
    m_product_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    layout->addWidget(m_product_list, 0);

    QHBoxLayout* button_layout = new QHBoxLayout;

    m_remove_button = new QPushButton(tr("Remove"));
    button_layout->addWidget(m_remove_button, 0, Qt::AlignLeft);

    m_add_button = new QPushButton(tr("Add"));
    button_layout->addWidget(m_add_button, 1, Qt::AlignRight);

    layout->addLayout(button_layout, 1);

    connect(m_add_button, &QPushButton::clicked, [this]() { emit AddButtonClicked(); });
    connect(m_remove_button, &QPushButton::clicked, this, &FirmWidget::RemoveSelectedItems);

    setLayout(layout);
}

void FirmWidget::AddProduct(int product_index)
{
    int row = m_product_list->count();
    while (row > 0 && static_cast<ProductListItem*>(m_product_list->item(row - 1))->GetIndex() > product_index)
        --row;

    m_product_list->insertItem(row, new ProductListItem(nullptr, product_index));    
}

void FirmWidget::ApplyCurrentMergers(std::shared_ptr<ModelInterface>& model) const
{
    for (int i = 0; i < m_product_list->count(); ++i)
    {
        for (int j = i + 1; j < m_product_list->count(); ++j)
        {
            int product_index1 = static_cast<ProductListItem const*>(m_product_list->item(i))->GetIndex();
            int product_index2 = static_cast<ProductListItem const*>(m_product_list->item(j))->GetIndex();
            model->Merge(product_index1, product_index2);
        }
    }
}

void FirmWidget::RemoveSelectedItems()
{
    for (QListWidgetItem* item : m_product_list->selectedItems())
    {
        emit RemoveButtonClicked(static_cast<ProductListItem*>(item)->GetIndex());
        delete m_product_list->takeItem(m_product_list->row(item));
    }
}