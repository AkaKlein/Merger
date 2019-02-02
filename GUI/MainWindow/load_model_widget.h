#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

#include "Models/model_type.h"

/// A widget to select a file from which to load a model.
class LoadModelWidget : public QWidget
{
    Q_OBJECT

public:
    /// Creates the widget with no file selected.
    LoadModelWidget();


signals:
    /// A signal that is emitted when the load button is clicked.
    void LoadData(std::string const& file_path);

    /// A signal that is emitted when the model type is changed.
    void ModelTypeChanged(ModelType model_type);

private slots:
    /// Changes #m_file_path_text to contain the path of the selected file and enables
    /// the #m_load_button.
    void SelectFile();

private:
    /// The layout that includes everything.
    QGridLayout* m_main_layout;
    
    /// A label for the model type combo box.
    QLabel* m_model_type_label;

    /// The combo box to select the type of model that will be loaded.
    QComboBox* m_model_type_combo_box;

    /// The line where the file path will be shown when a file is selected.
    QLineEdit* m_file_path_text;

    /// A button to select a file.
    QPushButton* m_select_file_button;

    /// A button to load the selected file.
    QPushButton* m_load_button;
};