#include "plot_chart.h"

#include <QtCharts/QLineSeries>
#include <QGesture>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Models/model_interface.h"

PlotChart::PlotChart(ModelInterface const& model, QGraphicsItem* parent, Qt::WindowFlags window_flags)
    : QtCharts::QChart(QChart::ChartTypeCartesian, parent, window_flags), m_model(model)
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
    removeAllSeries();

    QtCharts::QLineSeries* series = new QtCharts::QLineSeries;
    ColumnVector optimum_prices = m_model.ComputePrices();

    double p_opt = optimum_prices[m_product_index];
    for (double p = p_opt * 0.9; p <= p_opt * 1.1; p += p_opt * 0.01)
    {
        ColumnVector prices = optimum_prices;
        prices[m_product_index] = p;
        *series << QPointF(m_model.ComputeQuantities(prices)[m_product_index], p);
    }

    addSeries(series);

    createDefaultAxes();
    axisX()->setTitleText("Quantity");
    axisY()->setTitleText("Price");
}
