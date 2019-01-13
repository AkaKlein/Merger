#include "model_widget.h"

#include <QFileDialog>

#include "Models/linear_demands_constant_costs.h"
#include "model_result.h"

ModelWidget::ModelWidget()
{
    // Text to display the path that has been selected.
    m_file_path_text = new QLineEdit;
    m_file_path_text->setReadOnly(true);
    m_file_path_text->setMinimumWidth(500);

    // Button to select the file.
    m_select_file_button = new QPushButton(tr("&Select file"));
    m_select_file_button->setToolTip(tr("Select the file to load the data from"));
    m_select_file_button->setFixedWidth(100);

    // Button to load the file once it has been selected.
    m_load_button = new QPushButton(tr("&Load data"));
    m_load_button->setToolTip(tr("Load data from a file"));
    m_load_button->setEnabled(false);
    m_load_button->setFixedWidth(100);

    // Add the elements to the layout
    m_main_layout = new QHBoxLayout;
    m_main_layout->addWidget(m_file_path_text, 0);
    m_main_layout->addWidget(m_select_file_button, 1);
    m_main_layout->addWidget(m_load_button, 2);

    // Add the connections
    connect(m_select_file_button, &QPushButton::clicked, this, &ModelWidget::SelectFile);
    connect(m_load_button, &QPushButton::clicked, this, &ModelWidget::LoadData);

    setLayout(m_main_layout);
}

void ModelWidget::SetCurrentModel(ModelType type)
{
    m_model_type = type;
}

void ModelWidget::SelectFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open data file"), "",
        tr("Data file (*.txt);;All Files (*)"));
    
    m_file_path_text->setText(file_name);
    m_load_button->setEnabled(true);
}

void ModelWidget::LoadData()
{
    // Create a model object with the selected type from the selected path.
    std::unique_ptr<ModelInterface> model;
    switch (m_model_type)
    {
        case ModelType::LinearDemandsConstantCosts:
        {
            model = std::make_unique<LinearDemandsConstantCosts>();
            model->LoadFromFile(m_file_path_text->text().toStdString());
            break;
        }
        case ModelType::LinearDemandsLinearCosts:
            throw std::runtime_error("Not implemented yet");
    }

    // Create and show the results window.
    ModelResult* result = new ModelResult(this, std::move(model), m_model_index++);
    result->show();
}