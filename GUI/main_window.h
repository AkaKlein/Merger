#pragma once

#include <QMainWindow>

#include "model_widget.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    ModelWidget* m_model_widget;
};
