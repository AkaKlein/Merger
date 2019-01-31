#include "plot_chart.h"

#include <QtCharts/QLineSeries>
#include <QGesture>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Models/model_interface.h"

PlotChart::PlotChart(ModelInterface const& model, QGraphicsItem* parent, Qt::WindowFlags window_flags)
    : QChart(QChart::ChartTypeCartesian, parent, window_flags), m_model(model)
{
    // Seems that QGraphicsView (QChartView) does not grab gestures.
    // They can only be grabbed here in the QGraphicsWidget (QChart).
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
    
    AddData();
}

bool PlotChart::sceneEvent(QEvent* event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QChart::event(event);
}

bool PlotChart::gestureEvent(QGestureEvent* event)
{
    if (QGesture* gesture = event->gesture(Qt::PanGesture)) 
    {
        QPanGesture* pan = static_cast<QPanGesture*>(gesture);
        QChart::scroll(-pan->delta().x(), pan->delta().y());
    }

    if (QGesture* gesture = event->gesture(Qt::PinchGesture)) 
    {
        QPinchGesture *pinch = static_cast<QPinchGesture*>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}

void PlotChart::AddData()
{
    ColumnVector optimum_prices = m_model.ComputePrices();

    QLineSeries* series = new QLineSeries;
    for (double p = optimum_prices[0] * 0.9; p <= optimum_prices[0] * 1.1; p += optimum_prices[0] * 0.01)
    {
        ColumnVector prices = optimum_prices;
        prices[0] = p;
        *series << QPointF(m_model.ComputeQuantities(prices)[0], p);
    }

    addSeries(series);
}