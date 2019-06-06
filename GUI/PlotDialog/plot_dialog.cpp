#include "plot_dialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "Models/model_interface.h"

#include "plot_chart.h"
#include "plot_chart_view.h"
#include "select_models_dialog.h"

PlotDialog::PlotDialog(QWidget* parent, int model_index, ModelInterface const& model)
    : QDialog(parent), m_model_index(model_index), m_model(model)
{
    m_selected_models_by_id[model_index] = model.Clone();

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

    // Create the button to be able to add other models.
    QPushButton* add_model_button = new QPushButton(tr("Show other models"));

    // Add the widget to the layout.
    options_layout->addWidget(add_model_button, 1);

    // Connect the button to its slot.
    connect(add_model_button, &QPushButton::clicked, this, &PlotDialog::ShowOtherModelsButtonClicked);

    // Add the horizontal layout.
    layout->addLayout(options_layout, 0);

    // Add the plot.
    m_plot_chart = new PlotChart(m_selected_models_by_id);
    m_plot_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Connect the product box to the chart.
    connect(product_box, qOverload<int>(&QComboBox::currentIndexChanged), m_plot_chart, &PlotChart::SelectedProductChanged);

    // Add the view that contains the plot.
    PlotChartView* plot_chart_view = new PlotChartView(m_plot_chart);
    plot_chart_view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(plot_chart_view, 1);

    // Grab gestures in the dialog.
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    // Set the layout and the title.
    setLayout(layout);
    setWindowTitle(tr("Plot Model %1").arg(model_index));

    // Resize the dialog and make it visible.
    resize(800, 600);
    show();
}

PlotDialog::~PlotDialog() = default;

void PlotDialog::AddModel(int id, std::shared_ptr<ModelInterface> const& model) 
{ 
    m_other_models_by_id[id] = model; 
}

void PlotDialog::RemoveModel(int id) 
{ 
    m_other_models_by_id.erase(id); 
    m_selected_models_by_id.erase(id);
    m_plot_chart->AddData();
}

void PlotDialog::ShowOtherModelsButtonClicked()
{
    SelectModelsDialog* dialog = new SelectModelsDialog(m_model_index, m_other_models_by_id, m_selected_models_by_id);
    dialog->exec();
    m_plot_chart->AddData();
}