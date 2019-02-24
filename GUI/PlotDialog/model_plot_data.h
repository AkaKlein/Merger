#pragma once

namespace QtCharts {
class QLineSeries;
}

class ModelPlotData
{
public:
    int m_model_index;
    QtCharts::QLineSeries* m_price_series;
    QtCharts::QLineSeries* m_profit_series;
    double m_price_start_range;
    double m_price_end_range;
    double m_profit_start_range;
    double m_profit_end_range;
    double m_quantity_start_range;
    double m_quantity_end_range;
};