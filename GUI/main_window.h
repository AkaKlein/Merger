#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    QWidget* m_central_widget;
    QGridLayout* m_main_layout;
    QPushButton* m_load_button;

private slots:
    void LoadData();
};
