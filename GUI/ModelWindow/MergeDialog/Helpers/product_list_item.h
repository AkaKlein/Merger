#pragma once

#include <QListWidgetItem>

class QListWidget;

class ProductListItem : public QListWidgetItem
{
public:
    ProductListItem(QListWidget* parent, int index)
        : QListWidgetItem(parent), m_index(index) 
    { 
        setText(QString("Product %1").arg(index + 1));
    }


    int GetIndex() const { return m_index; }

private:
    int m_index;
};