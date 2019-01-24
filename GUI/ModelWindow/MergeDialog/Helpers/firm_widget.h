#pragma once

#include <memory>

#include <QWidget>

class ModelInterface;
class QListWidget;
class QPushButton;

class FirmWidget : public QWidget
{
    Q_OBJECT

public:
    FirmWidget(QWidget* parent = nullptr);

    void AddProduct(int product_index);
    void ApplyCurrentMergers(std::shared_ptr<ModelInterface>& model) const;

signals:
    void AddButtonClicked();
    void RemoveButtonClicked(int product_index);

private slots:
    void RemoveSelectedItems();

private:
    QListWidget* m_product_list;
    QPushButton* m_remove_button;
    QPushButton* m_add_button;
};