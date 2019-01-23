#pragma once

#include <QWidget>

class QListWidget;
class QPushButton;

class FirmWidget : public QWidget
{
    Q_OBJECT

public:
    FirmWidget(QWidget* parent = nullptr);

private:
    QListWidget* m_product_list;
    QPushButton* m_remove_button;
    QPushButton* m_add_button;
};