#pragma once

#include <QtCharts/QChartView>
#include <QRubberBand>


class PlotChartView : public QtCharts::QChartView
{
public:
    PlotChartView(QtCharts::QChart* chart, QWidget* parent = 0);

protected:
    virtual bool viewportEvent(QEvent* event) override final;
    virtual void mousePressEvent(QMouseEvent* event) override final;
    virtual void mouseMoveEvent(QMouseEvent* event) override final;
    virtual void mouseReleaseEvent(QMouseEvent* event) override final;
    virtual void keyPressEvent(QKeyEvent* event) override final;

private:
    bool m_is_touching = false;
};