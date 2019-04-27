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

void MultiProductFirmsWidget::AddProduct(int firm_index, int product_index)
{
    while (firm_index >= static_cast<int>(m_firm_widgets.size()))
        CreateNewFirm();

    m_firm_widgets[firm_index]->AddProduct(product_index);
}

void MultiProductFirmsWidget::ApplyCurrentMergers(std::shared_ptr<ModelInterface>& model) const
{
    for (FirmWidget const* firm_widget : m_firm_widgets)
        firm_widget->ApplyCurrentMergers(model);
}

void MultiProductFirmsWidget::CreateNewFirm()
{
    FirmWidget* firm_widget = new FirmWidget;
    int firm_index = m_firm_widgets.size();
    m_layout->insertWidget(firm_index, firm_widget);
    m_firm_widgets.push_back(firm_widget);

    connect(firm_widget, &FirmWidget::AddButtonClicked, [this, firm_index]() { emit AddButtonClicked(firm_index); });
    connect(firm_widget, &FirmWidget::RemoveButtonClicked, [this](int product_index) { emit RemoveButtonClicked(product_index); });
}