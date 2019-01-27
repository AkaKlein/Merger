#include "merge_widget.h"

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.h"
#include "GUI/ModelWindow/MergeDialog/Helpers/product_list_item.h"
#include "Models/model_interface.h"

MergeWidget::MergeWidget(QWidget* parent, ModelInterface const& model)
    : QWidget(parent), m_model(model)
{
    // Create a grid layout.
    QGridLayout* layout = new QGridLayout;

    // Create the label for the monoproduct firms.
    QLabel* mono_product_firms_label = new QLabel(tr("Single products"));
    layout->addWidget(mono_product_firms_label, 0, 0, Qt::AlignCenter);

    // Create the label for the firms with more products.
    QLabel* multi_product_firms_label = new QLabel(tr("Product groups"));
    layout->addWidget(multi_product_firms_label, 0, 1, Qt::AlignCenter);

    // Create the list to show the monoproduct firms.
    m_mono_product_firms_list = new QListWidget(this);
    m_mono_product_firms_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    layout->addWidget(m_mono_product_firms_list, 1, 0);

    // Create the widget to show the different firms with more than one product.
    m_multi_product_firms_widget = new MultiProductFirmsWidget(this);
    layout->addWidget(m_multi_product_firms_widget, 1, 1);

    // Create the cancel button.
    QPushButton* cancel_button = new QPushButton(tr("&Cancel"));
    cancel_button->setFixedWidth(100);
    layout->addWidget(cancel_button, 2, 0, Qt::AlignLeft);
    connect(cancel_button, &QPushButton::clicked, [this]() { emit CancelButtonClicked(); });

    // Create the apply button.
    QPushButton* apply_button = new QPushButton(tr("&Apply"));
    apply_button->setFixedWidth(100);
    layout->addWidget(apply_button, 2, 1, Qt::AlignRight);
    connect(apply_button, &QPushButton::clicked, [this]() { emit ApplyButtonClicked(GetCurrentModel()); });

    // Set the layout.
    setLayout(layout);

    // Connect the button events in the firms widget.
    connect(m_multi_product_firms_widget, &MultiProductFirmsWidget::AddButtonClicked, this, &MergeWidget::AddButtonClicked);
    connect(m_multi_product_firms_widget, &MultiProductFirmsWidget::RemoveButtonClicked, this, &MergeWidget::RemoveButtonClicked);

    // Fill the widget taking into account the current firms in the model.
    Initialize();
}

void MergeWidget::AddButtonClicked(int firm_index)
{
    for (QListWidgetItem* item : m_mono_product_firms_list->selectedItems())
    {
        m_multi_product_firms_widget->AddProduct(firm_index, static_cast<ProductListItem*>(item)->GetIndex());
        delete m_mono_product_firms_list->takeItem(m_mono_product_firms_list->row(item));
    }
}

void MergeWidget::RemoveButtonClicked(int product_index)
{
    int row = m_mono_product_firms_list->count();
    while (row > 0 && static_cast<ProductListItem*>(m_mono_product_firms_list->item(row - 1))->GetIndex() > product_index)
        --row;

    m_mono_product_firms_list->insertItem(row, new ProductListItem(nullptr, product_index));
}

void MergeWidget::Initialize()
{
    std::vector<int> product_group(m_model.GetNumberOfProducts(), -1);
    int current_group = 0;

    for (int i = 0; i < m_model.GetNumberOfProducts(); ++i)
    {
        // No group so far, start one with it.
        if (product_group[i] == -1)
        {
            int members_in_group = 1;
            product_group[i] = current_group;

            // No point in starting with previous products, as they cannot be in the same firm.
            for (int j = i + 1; j < m_model.GetNumberOfProducts(); ++j)
            {
                if (m_model.AreProducedBySameFirm(i, j))
                {
                    product_group[j] = current_group;
                    m_multi_product_firms_widget->AddProduct(current_group, j);
                    ++members_in_group;
                }
            }

            if (members_in_group > 1)
                m_multi_product_firms_widget->AddProduct(current_group, i);
            else
                RemoveButtonClicked(i);

            ++current_group;
        }
    }
}

std::shared_ptr<ModelInterface> MergeWidget::GetCurrentModel() const
{
    std::shared_ptr<ModelInterface> current_model = m_model.CloneWithoutMergers();
    m_multi_product_firms_widget->ApplyCurrentMergers(current_model);
    return current_model;
}