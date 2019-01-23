#include "merge_dialog.h"

#include <QVBoxLayout>

#include "merge_widget.h"

MergeDialog::MergeDialog(QWidget* parent, ModelInterface const& model)
    : QDialog(parent)
{
    m_merge_widget = new MergeWidget(this, model);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_merge_widget);
    setLayout(layout);

    open();
}