#pragma once

#include <QDialog>

class MergeWidget;
class ModelInterface;

class MergeDialog : public QDialog
{
    Q_OBJECT

public:
    MergeDialog(QWidget* parent, ModelInterface const& model);

private:
    MergeWidget* m_merge_widget;
};