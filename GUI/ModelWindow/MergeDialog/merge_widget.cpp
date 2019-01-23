#include "merge_widget.h"

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.h"

MergeWidget::MergeWidget(QWidget* parent, ModelInterface const& model)
    : QWidget(parent)
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
    layout->addWidget(m_mono_product_firms_list, 1, 0);

    // Create the widget to show the different firms with more than one product.
    m_multi_product_firms_widget = new MultiProductFirmsWidget(this);
    layout->addWidget(m_multi_product_firms_widget, 1, 1);

    // Create the cancel button.
    QPushButton* cancel_button = new QPushButton(tr("&Cancel"));
    cancel_button->setFixedWidth(100);
    layout->addWidget(cancel_button, 2, 0, Qt::AlignLeft);

    // Create the apply button.
    QPushButton* apply_button = new QPushButton(tr("&Apply"));
    apply_button->setFixedWidth(100);
    layout->addWidget(apply_button, 2, 1, Qt::AlignRight);

    // Set the layout.
    setLayout(layout);
}