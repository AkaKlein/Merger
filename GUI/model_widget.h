#pragma once

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

#include "Models/model_type.h"

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    ModelWidget();

    void SetCurrentModel(ModelType type);

private slots:
    void SelectFile();
    void LoadData();

private:
    QHBoxLayout* m_main_layout;
    QLineEdit* m_file_path_text;
    QPushButton* m_select_file_button;
    QPushButton* m_load_button;

    int m_model_index = 1;
    ModelType m_model_type;
};