#include "main_window.h"

#include <iostream>

#include <QFileDialog>

MainWindow::MainWindow()
{
    m_central_widget = new QWidget;

    m_main_layout = new QGridLayout;

    m_load_button = new QPushButton(tr("&Load data"));
    m_load_button->setToolTip(tr("Load data from a file"));

    m_main_layout->addWidget(m_load_button, 0, 1);

    m_central_widget->setLayout(m_main_layout);

    setCentralWidget(m_central_widget);

    connect(m_load_button, &QPushButton::clicked, this, &MainWindow::LoadData);
}

void MainWindow::LoadData()
{
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open data file"), "",
        tr("Data file (*.txt);;All Files (*)"));

    std::cout << file_name.toStdString() << std::endl;
}
