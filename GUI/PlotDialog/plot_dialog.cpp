#include "plot_dialog.h"

#include <QVBoxLayout>

#include "plot_chart.h"
#include "plot_chart_view.h"

PlotDialog::PlotDialog(QWidget* parent, int model_index, ModelInterface const& model)
    : QDialog(parent), m_model(model)
{
    // Create the layout.
    QVBoxLayout* layout = new QVBoxLayout;

    // Add the plot.
    PlotChart* plot_chart = new PlotChart(model);
    plot_chart->setAnimationOptions(QChart::SeriesAnimations);
    plot_chart->legend()->hide();
    plot_chart->createDefaultAxes();
    plot_chart->axisX()->setTitleText("Quantity");
    plot_chart->axisY()->setTitleText("Price");

    // Add the view that contains the plot.
    PlotChartView* plot_chart_view = new PlotChartView(plot_chart);
    plot_chart_view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(plot_chart_view);

    // Grab gestures in the dialog.
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    // Set the layout and the title.
    setLayout(layout);
    setWindowTitle(tr("Plot Model %1").arg(model_index));

    // Resize the dialog and make it visible.
    resize(400, 300);
    show();
}