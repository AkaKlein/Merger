#pragma once

#include <memory>

#include <QWidget>

class ModelInterface;
class MultiProductFirmsWidget;
class QListWidget;

class MergeWidget : public QWidget
{
    Q_OBJECT

public:
    MergeWidget(QWidget* parent, ModelInterface const& model);

signals:
    void CancelButtonClicked();
    void ApplyButtonClicked(std::shared_ptr<ModelInterface> model);

private slots:
    void AddButtonClicked(int firm_index);
    void RemoveButtonClicked(int product_index);

private:
    void Initialize();
    std::shared_ptr<ModelInterface> GetCurrentModel() const;

    ModelInterface const& m_model;
    QListWidget* m_mono_product_firms_list;
    MultiProductFirmsWidget* m_multi_product_firms_widget;
};