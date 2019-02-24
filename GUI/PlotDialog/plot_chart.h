#pragma once

#include <memory>

#include <QtCharts/QChart>

#include "model_plot_data.h"

class ModelInterface;
class QGestureEvent;

namespace QtCharts {
class QLineSeries;
}

class PlotChart : public QtCharts::QChart
{
public:
    PlotChart(
        std::map<int, std::shared_ptr<ModelInterface>> const& selected_models_by_id, 
        QGraphicsItem* parent = nullptr, 
        Qt::WindowFlags window_flags = 0);

    void AddData();

public slots:
    void SelectedProductChanged(int product_index);

protected:
    virtual bool sceneEvent(QEvent* event) override final;

private:
    bool gestureEvent(QGestureEvent* event);
    ModelPlotData ComputeDataForModel(int model_index, ModelInterface const& model) const;
    
    std::map<int, std::shared_ptr<ModelInterface>> const& m_selected_models_by_id;
    QtCharts::QLineSeries* m_series;
    int m_product_index = 0;
};