#include "multi_product_firms_widget.h"

#include <QPushButton>
#include <QVBoxLayout>

#include "firm_widget.h"

MultiProductFirmsWidget::MultiProductFirmsWidget(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout;

    m_push_button = new QPushButton(tr("Add group"));
    m_push_button->setFixedWidth(100);
    m_layout->addWidget(m_push_button, 1, Qt::AlignCenter);

    setLayout(m_layout);

    connect(m_push_button, &QPushButton::clicked, this, &MultiProductFirmsWidget::CreateNewFirm);
}

void MultiProductFirmsWidget::CreateNewFirm()
{
    FirmWidget* firm_widget = new FirmWidget;
    m_layout->insertWidget(m_firm_widgets.size(), firm_widget);
    m_firm_widgets.push_back(firm_widget);
}