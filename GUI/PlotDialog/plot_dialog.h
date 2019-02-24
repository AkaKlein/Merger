#pragma once

#include <map>
#include <memory>
#include <string>

#include <QDialog>

class ModelInterface;
class PlotChart;
class QWidget;

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    PlotDialog(QWidget* parent, int model_index, ModelInterface const& model);
    ~PlotDialog();

    void AddModel(int id, std::shared_ptr<ModelInterface> const& model);
    void RemoveModel(int id);

private slots:
    void ShowOtherModelsButtonClicked();

private:
    int m_model_index;
    ModelInterface const& m_model;
    std::map<int, std::shared_ptr<ModelInterface>> m_other_models_by_id;
    std::map<int, std::shared_ptr<ModelInterface>> m_selected_models_by_id;
    PlotChart* m_plot_chart;
};

