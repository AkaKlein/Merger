#pragma once

#include <QDialog>

class ModelInterface;
class QWidget;

class PlotDialog : public QDialog
{
public:
    PlotDialog(QWidget* parent, int model_index, ModelInterface const& model);

private:
    ModelInterface const& m_model;
};