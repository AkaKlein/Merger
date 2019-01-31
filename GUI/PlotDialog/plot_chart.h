#pragma once

#include <QtCharts/QChart>

class ModelInterface;
class QGestureEvent;

QT_CHARTS_USE_NAMESPACE

class PlotChart : public QChart
{
public:
    PlotChart(ModelInterface const& model, QGraphicsItem* parent = nullptr, Qt::WindowFlags window_flags = 0);

protected:
    virtual bool sceneEvent(QEvent* event) override final;

private:
    bool gestureEvent(QGestureEvent* event);
    
    void AddData();

    ModelInterface const& m_model;
};