#pragma once

#include <memory>

#include <QDialog>

class ModelInterface;
class QCheckBox;

class SelectModelsDialog : public QDialog
{
    Q_OBJECT

public:
    SelectModelsDialog(
        int model_index,
        std::map<int, std::shared_ptr<ModelInterface>> const& other_models_by_id,
        std::map<int, std::shared_ptr<ModelInterface>>& selected_models_by_id);

private slots:
    void ApplyClicked();

private:
    int m_model_index;
    std::map<int, std::shared_ptr<ModelInterface>> const& m_other_models_by_id;
    std::map<int, std::shared_ptr<ModelInterface>>& m_selected_models_by_id;
    std::map<int, QCheckBox*> m_check_boxes;
};