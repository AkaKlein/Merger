#pragma once

#include <QTableView>

class BaseTableView : public QTableView
{
public:
    using QTableView::QTableView;

protected:
    virtual void keyPressEvent(QKeyEvent* event) override final;
    virtual QSize sizeHint() const override final;
};