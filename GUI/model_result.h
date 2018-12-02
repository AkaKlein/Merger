#pragma once

#include <QDialog>
#include <QTableWidget>

class ModelResult : public QDialog
{
public:
    ModelResult(QWidget* parent);

private:
    QTableWidget* m_table_widget;
};