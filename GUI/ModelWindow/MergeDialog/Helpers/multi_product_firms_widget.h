#pragma once

#include <memory>

#include <QWidget>

class FirmWidget;
class ModelInterface;
class QPushButton;
class QVBoxLayout;

class MultiProductFirmsWidget : public QWidget
{
    Q_OBJECT

public:
    MultiProductFirmsWidget(QWidget* parent);

    void AddProduct(int firm_index, int product_index);
    void ApplyCurrentMergers(std::shared_ptr<ModelInterface>& model) const;

signals:
    void AddButtonClicked(int firm_index);
    void RemoveButtonClicked(int product_index);

private slots:
    void CreateNewFirm();

private:
    std::vector<FirmWidget*> m_firm_widgets;
    QPushButton* m_push_button;
    QVBoxLayout* m_layout;
};