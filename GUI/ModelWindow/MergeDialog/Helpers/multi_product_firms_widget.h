#pragma once

#include <QWidget>

class FirmWidget;
class QPushButton;
class QVBoxLayout;

class MultiProductFirmsWidget : public QWidget
{
    Q_OBJECT

public:
    MultiProductFirmsWidget(QWidget* parent);

private slots:
    void CreateNewFirm();

private:
    std::vector<FirmWidget*> m_firm_widgets;
    QPushButton* m_push_button;
    QVBoxLayout* m_layout;
};