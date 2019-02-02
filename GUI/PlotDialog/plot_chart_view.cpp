#include "plot_chart_view.h"

#include <QMouseEvent>

PlotChartView::PlotChartView(QtCharts::QChart* chart, QWidget* parent) 
    : QtCharts::QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

bool PlotChartView::viewportEvent(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin) 
    {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_is_touching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QtCharts::QChart::NoAnimation);
    }
    return QtCharts::QChartView::viewportEvent(event);
}

void PlotChartView::mousePressEvent(QMouseEvent* event)
{
    if (m_is_touching)
        return;

    QtCharts::QChartView::mousePressEvent(event);
}

void PlotChartView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_is_touching)
        return;

    QtCharts::QChartView::mouseMoveEvent(event);
}

void PlotChartView::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_is_touching)
        m_is_touching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView::mouseReleaseEvent(event);
}

void PlotChartView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) 
    {
        case Qt::Key_Plus:
            chart()->zoomIn();
            break;
        case Qt::Key_Minus:
            chart()->zoomOut();
            break;
        case Qt::Key_Left:
            chart()->scroll(-10, 0);
            break;
        case Qt::Key_Right:
            chart()->scroll(10, 0);
            break;
        case Qt::Key_Up:
            chart()->scroll(0, 10);
            break;
        case Qt::Key_Down:
            chart()->scroll(0, -10);
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}