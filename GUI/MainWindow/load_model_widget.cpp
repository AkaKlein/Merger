#include "load_model_widget.h"

#include <QFileDialog>

LoadModelWidget::LoadModelWidget()
{
    // Create the label for the model type combo box.
    m_model_type_label = new QLabel(tr("Model type"));

    // Create a combo box will all the types of models.
    m_model_type_combo_box = new QComboBox;
    for (int i = 0; i < static_cast<int>(ModelType::Count); ++i)
    {
        ModelType model_type = static_cast<ModelType>(i);
        m_model_type_combo_box->addItem(QString::fromStdString(ModelTypeToExtendedString(model_type)));
    }

    // Emit a signal when the model type is changed.
    connect(m_model_type_combo_box, qOverload<int>(&QComboBox::currentIndexChanged), [this](int) { emit ModelTypeChanged(); });

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
    m_main_layout = new QGridLayout;
    m_main_layout->addWidget(m_model_type_label, 0, 0);
    m_main_layout->addWidget(m_model_type_combo_box, 0, 1);
    m_main_layout->addWidget(m_file_path_text, 1, 0, 1, 2);
    m_main_layout->addWidget(m_select_file_button, 1, 2);
    m_main_layout->addWidget(m_load_button, 1, 3, Qt::AlignRight);

    // Add the connections
    connect(m_select_file_button, &QPushButton::clicked, this, &LoadModelWidget::SelectFile);
    connect(m_load_button, &QPushButton::clicked, [this]() { emit LoadData(m_file_path_text->text().toStdString()); });

    setLayout(m_main_layout);
}

ModelType LoadModelWidget::GetSelectedModelType() const
{
    return static_cast<ModelType>(m_model_type_combo_box->currentIndex());
}

void LoadModelWidget::SelectFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open data file"), "",
        tr("Data file (*.txt);;All Files (*)"));
    
    m_file_path_text->setText(file_name);
    m_load_button->setEnabled(true);
}