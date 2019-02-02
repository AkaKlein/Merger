#include "plot_dialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Models/model_interface.h"

#include "plot_chart.h"
#include "plot_chart_view.h"

PlotDialog::PlotDialog(QWidget* parent, int model_index, ModelInterface const& model)
    : QDialog(parent), m_model(model)
{
    // Create the layout.
    QVBoxLayout* layout = new QVBoxLayout;

    // Create a horizontal layout to hold the combobox and the compare button.
    QHBoxLayout* options_layout = new QHBoxLayout;
    
    // Create the combobox to select the product to plot.
    QComboBox* product_box = new QComboBox;
    for (int i = 0; i < model.GetNumberOfProducts(); ++i)
        product_box->addItem(tr("Product %1").arg(i + 1));
    
    // Add the widget to the layout.
    options_layout->addWidget(product_box, 0);

    // Add the horizontal layout.
    layout->addLayout(options_layout, 0);

    // Add the plot.
    PlotChart* plot_chart = new PlotChart(model);
    plot_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    plot_chart->legend()->hide();

    // Connect the product box to the chart.
    connect(product_box, qOverload<int>(&QComboBox::currentIndexChanged), plot_chart, &PlotChart::SelectedProductChanged);

    // Add the view that contains the plot.
    PlotChartView* plot_chart_view = new PlotChartView(plot_chart);
    plot_chart_view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(plot_chart_view, 1);

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