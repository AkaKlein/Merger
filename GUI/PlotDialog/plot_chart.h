#pragma once

#include <QtCharts/QChart>

class ModelInterface;
class QGestureEvent;

namespace QtCharts {
class QLineSeries;
}

class PlotChart : public QtCharts::QChart
{
public:
    PlotChart(ModelInterface const& model, QGraphicsItem* parent = nullptr, Qt::WindowFlags window_flags = 0);

public slots:
    void SelectedProductChanged(int product_index);

protected:
    virtual bool sceneEvent(QEvent* event) override final;

private:
    bool gestureEvent(QGestureEvent* event);
    void AddData();    
    
    ModelInterface const& m_model;
    QtCharts::QLineSeries* m_series;
    int m_product_index = 0;
};