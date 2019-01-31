#pragma once

#include <QtCharts/QChartView>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE

class PlotChartView : public QChartView
{
public:
    PlotChartView(QChart* chart, QWidget* parent = 0);

protected:
    virtual bool viewportEvent(QEvent* event) override final;
    virtual void mousePressEvent(QMouseEvent* event) override final;
    virtual void mouseMoveEvent(QMouseEvent* event) override final;
    virtual void mouseReleaseEvent(QMouseEvent* event) override final;
    virtual void keyPressEvent(QKeyEvent* event) override final;

private:
    bool m_is_touching = false;
};