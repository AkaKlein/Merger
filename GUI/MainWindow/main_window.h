#pragma once

#include <QMainWindow>

#include "Models/model_type.h"

class LoadModelWidget;
class ModelWindow;

/// The main window of the program. It allows to load models from files and show 
/// their results.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Creates all the menus of the main window and connects its widget so
    /// that whenever the user tries to load a model, it opens a new ModelWindow.
    MainWindow();


private slots:
    /// Creates a ModelWindow with a model loaded from a file.
    ///
    /// @param file_path The path from where the model is loaded.
    void LoadModel(std::string const& file_path);

private:
    /// A pointer to widget that allows the user to load a model from a file.
    LoadModelWidget* m_load_model_widget;

    /// The type of model that is selected to be loaded.
    ModelType m_selected_model_type;

    /// The index that the next model created will have.
    int m_model_index = 1;

    /// A vector containing all the opened model windows.
    std::vector<ModelWindow*> m_model_windows;
};
