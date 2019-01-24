#pragma once

#include <memory>

#include <QDialog>

class MergeWidget;
class ModelInterface;

class MergeDialog : public QDialog
{
    Q_OBJECT

public:
    MergeDialog(QWidget* parent, ModelInterface const& model);

signals:
    void ApplyButtonClicked(std::shared_ptr<ModelInterface> model);

private:
    MergeWidget* m_merge_widget;
};