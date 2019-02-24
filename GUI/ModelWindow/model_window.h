#pragma once

#include <map>
#include <memory>

#include <QMainWindow>

#include "Models/model_type.h"

class ModelInterface;
class ModelTableView;
class PlotDialog;
class QAction;
class QMenu;

class ModelWindow : public QMainWindow
{
    Q_OBJECT

public:
    ModelWindow(QWidget* parent, std::string const& file_path, ModelType model_type, int model_index,
                std::vector<ModelWindow*>& model_windows);
    
    ModelWindow(QWidget* parent, std::shared_ptr<ModelInterface>& model, int model_index,
                std::vector<ModelWindow*>& model_windows);

    int GetModelIndex() const { return m_model_index; }

    void ReportModelCreated(int id, std::shared_ptr<ModelInterface> const& model);
    void ReportModelDeleted(int id);

signals:
    void CreateNewModelWindow(std::shared_ptr<ModelInterface> model);

private slots:
    void MergeClicked();
    void PlotClicked();
    void CompareClicked(int model_index);

private:
    void Initialize(ModelType model_type, int model_index);
    void AddCompareAction(int model_index);
    virtual void closeEvent(QCloseEvent* event) override final;

    int m_model_index;
    
    std::vector<ModelWindow*>& m_model_windows;

    ModelTableView* m_model_table_view;
    QMenu* m_compare_menu;

    std::map<int, QAction*> m_compare_actions;

    std::vector<PlotDialog*> m_plot_dialogs;
};