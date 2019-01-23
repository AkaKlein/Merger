#pragma once

#include <QWidget>

class ModelInterface;
class MultiProductFirmsWidget;
class QListWidget;

class MergeWidget : public QWidget
{
    Q_OBJECT

public:
    MergeWidget(QWidget* parent, ModelInterface const& model);

private:
    QListWidget* m_mono_product_firms_list;
    MultiProductFirmsWidget* m_multi_product_firms_widget;
};