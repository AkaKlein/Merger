#include "firm_widget.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

FirmWidget::FirmWidget(QWidget* parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    m_product_list = new QListWidget;
    layout->addWidget(m_product_list, 0);

    QHBoxLayout* button_layout = new QHBoxLayout;

    m_remove_button = new QPushButton(tr("Remove"));
    button_layout->addWidget(m_remove_button, 0, Qt::AlignLeft);

    m_add_button = new QPushButton(tr("Add"));
    button_layout->addWidget(m_add_button, 1, Qt::AlignRight);

    layout->addLayout(button_layout, 1);

    setLayout(layout);
}