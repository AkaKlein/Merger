#include "plot_chart.h"

#include <cmath>

#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QGesture>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Models/model_interface.h"

PlotChart::PlotChart(
    std::map<int, std::shared_ptr<ModelInterface>> const& selected_models_by_id, 
    QGraphicsItem* parent, 
    Qt::WindowFlags window_flags)
    : 
    QtCharts::QChart(QChart::ChartTypeCartesian, parent, window_flags), 
    m_selected_models_by_id(selected_models_by_id)
{
    // Seems that QGraphicsView (QChartView) does not grab gestures.
    // They can only be grabbed here in the QGraphicsWidget (QChart).
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    AddData();
}

void PlotChart::SelectedProductChanged(int product_index)
{
    m_product_index = product_index;
    AddData();
}

bool PlotChart::sceneEvent(QEvent* event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QtCharts::QChart::event(event);
}

bool PlotChart::gestureEvent(QGestureEvent* event)
{
    if (QGesture* gesture = event->gesture(Qt::PanGesture)) 
    {
        QPanGesture* pan = static_cast<QPanGesture*>(gesture);
        QtCharts::QChart::scroll(-pan->delta().x(), pan->delta().y());
    }

    if (QGesture* gesture = event->gesture(Qt::PinchGesture)) 
    {
        QPinchGesture *pinch = static_cast<QPinchGesture*>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QtCharts::QChart::zoom(pinch->scaleFactor());
    }

    return true;
}

void PlotChart::AddData()
{
    // Remove everything from before.
    removeAllSeries();
    for (QtCharts::QAbstractAxis* axis : axes())
        removeAxis(axis);

    // Obtain the data for every selected model.
    std::vector<ModelPlotData> data_vector;
    for (auto const& kv : m_selected_models_by_id)
        data_vector.push_back(ComputeDataForModel(kv.first, *kv.second));

    // Get the interval of each axis.
    double price_start_range = std::numeric_limits<double>::max();
    double price_end_range = std::numeric_limits<double>::min();
    double profit_start_range = std::numeric_limits<double>::max();
    double profit_end_range = std::numeric_limits<double>::min();
    double quantity_start_range = std::numeric_limits<double>::max();
    double quantity_end_range = std::numeric_limits<double>::min();

    for (ModelPlotData const& data : data_vector)
    {
        price_start_range = std::min(price_start_range, data.m_price_start_range);
        price_end_range = std::max(price_end_range, data.m_price_end_range);
        profit_start_range = std::min(profit_start_range, data.m_profit_start_range);
        profit_end_range = std::max(profit_end_range, data.m_profit_end_range);
        quantity_start_range = std::min(quantity_start_range, data.m_quantity_start_range);
        quantity_end_range = std::max(quantity_end_range, data.m_quantity_end_range);
    }

    // Add the axes.
    QtCharts::QValueAxis* x_axis = new QtCharts::QValueAxis;
    x_axis->setTitleText("Quantity");
    x_axis->setRange(quantity_start_range, quantity_end_range);
    addAxis(x_axis, Qt::AlignBottom);

    QtCharts::QValueAxis* left_axis = new QtCharts::QValueAxis;
    left_axis->setTitleText("Price");
    left_axis->setRange(price_start_range, price_end_range);
    addAxis(left_axis, Qt::AlignLeft);

    QtCharts::QValueAxis* right_axis = new QtCharts::QValueAxis;
    right_axis->setTitleText("Firm Profit");
    right_axis->setRange(profit_start_range, profit_end_range);
    addAxis(right_axis, Qt::AlignRight);

    // Add the series
    for (ModelPlotData const& data : data_vector)
    {
        addSeries(data.m_price_series);
        data.m_price_series->attachAxis(x_axis);
        data.m_price_series->attachAxis(left_axis);

        addSeries(data.m_profit_series);
        data.m_profit_series->attachAxis(x_axis);
        data.m_profit_series->attachAxis(right_axis);
    }
}

ModelPlotData PlotChart::ComputeDataForModel(int /*model_index*/, ModelInterface const& model) const
{
    ModelPlotData result;

    // Initialize the series.
    result.m_price_series = new QtCharts::QLineSeries;
    result.m_profit_series = new QtCharts::QLineSeries;

    // Initialize the ranges.
    ColumnVector optimum_prices = model.ComputePrices();
    result.m_price_start_range = 0.9 * optimum_prices[m_product_index];
    result.m_price_end_range = 1.1 * optimum_prices[m_product_index];
    result.m_profit_start_range = std::numeric_limits<double>::max();
    result.m_profit_end_range = std::numeric_limits<double>::min();
    result.m_quantity_start_range = std::numeric_limits<double>::max();
    result.m_quantity_end_range = std::numeric_limits<double>::min();
    if (result.m_price_start_range > result.m_price_end_range)
        std::swap(result.m_price_start_range, result.m_price_end_range);

    // Populate the series and update the ranges.
    for (double p = result.m_price_start_range; p <= result.m_price_end_range; p += std::fabs(optimum_prices[m_product_index]) * 0.01)
    {
        // Change the price of the selected product.
        ColumnVector prices = optimum_prices;
        prices[m_product_index] = p;

        // Compute the quantity with the changed price.
        double quantity = model.ComputeQuantities(prices)[m_product_index];

        // Compute the profit with the changed price.
        ColumnVector profits = model.ComputeProfits(prices);
        double firm_profit = 0;
        for (int i = 0; i < profits.Size(); ++i)
        {
            if (model.AreProducedBySameFirm(i, m_product_index))
                firm_profit += profits[i];
        }

        // Add the points to the series.
        *result.m_price_series << QPointF(quantity, p);
        *result.m_profit_series << QPointF(quantity, firm_profit);

        // Update the ranges.
        result.m_profit_start_range = std::min(result.m_profit_start_range, firm_profit);
        result.m_profit_end_range = std::max(result.m_profit_end_range, firm_profit);
        result.m_quantity_start_range = std::min(result.m_quantity_start_range, quantity);
        result.m_quantity_end_range = std::max(result.m_quantity_end_range, quantity);
    }

    // We want the maximum profit to be at the middle, so adjust the range.
    result.m_profit_end_range += result.m_profit_end_range - result.m_profit_start_range;

    return result;
}
