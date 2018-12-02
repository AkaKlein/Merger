#pragma once

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    ModelWidget();

private slots:
    void SelectFile();
    void LoadData();

private:
    QVBoxLayout* m_main_layout;

    QHBoxLayout* m_load_data_layout;
    QLineEdit* m_file_path_text;
    QPushButton* m_select_file_button;
    QPushButton* m_load_button;
};