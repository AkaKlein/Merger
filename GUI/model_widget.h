#pragma once

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    ModelWidget();

private slots:
    void SelectFile();
    void LoadData();

private:
    QHBoxLayout* m_main_layout;
    QLineEdit* m_file_path_text;
    QPushButton* m_select_file_button;
    QPushButton* m_load_button;
};