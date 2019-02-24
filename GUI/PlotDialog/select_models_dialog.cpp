#include "select_models_dialog.h"

#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "Models/model_interface.h"

SelectModelsDialog::SelectModelsDialog(
    int model_index,
    std::map<int, std::shared_ptr<ModelInterface>> const& other_models_by_id,
    std::map<int, std::shared_ptr<ModelInterface>>& selected_models_by_id)
    :
    m_model_index(model_index),
    m_other_models_by_id(other_models_by_id),
    m_selected_models_by_id(selected_models_by_id)
{
    // Create the layout.
    QVBoxLayout* layout = new QVBoxLayout;

    // Add the check boxes.
    int position = 0;
    for (auto const& kv : other_models_by_id)
    {
        if (kv.first != m_model_index)
        {
            QCheckBox* check_box = new QCheckBox(tr("Model %1").arg(kv.first));
            m_check_boxes[kv.first] = check_box;

            // Check it if it was already selected.
            if (selected_models_by_id.count(kv.first))
                check_box->setChecked(true);
            
            layout->addWidget(check_box, ++position);   
        }
    }

    // Add an apply button.
    QPushButton* apply_button = new QPushButton(tr("Apply"));
    layout->addWidget(apply_button, position);
    connect(apply_button, &QPushButton::clicked, this, &SelectModelsDialog::ApplyClicked);

    // Set the layout and the title.
    setLayout(layout);
    setWindowTitle(tr("Choose"));
}

void SelectModelsDialog::ApplyClicked()
{
    // Keep a copy of our model.
    std::shared_ptr<ModelInterface> own_model = m_selected_models_by_id[m_model_index];
    
    // Clear the map and add all the selected models.
    m_selected_models_by_id.clear();
    for (auto const& kv : m_check_boxes)
    {
        if (kv.second->isChecked())
            m_selected_models_by_id[kv.first] = m_other_models_by_id.at(kv.first);
    }

    // Add back our own model.
    m_selected_models_by_id[m_model_index] = own_model;

    close();
}