#-------------------------------------------------
#
# Project created by QtCreator 2019-04-28T14:04:05
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Merger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        GUI/Common/base_table_view.cpp \
        GUI/CompareDialog/compare_table_data.cpp \
        GUI/CompareDialog/compare_table_view.cpp \
        GUI/MainWindow/load_model_widget.cpp \
        GUI/MainWindow/main_window.cpp \
        GUI/ModelWindow/MergeDialog/Helpers/firm_widget.cpp \
        GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.cpp \
        GUI/ModelWindow/MergeDialog/merge_dialog.cpp \
        GUI/ModelWindow/MergeDialog/merge_widget.cpp \
        GUI/ModelWindow/model_table_data.cpp \
        GUI/ModelWindow/model_table_view.cpp \
        GUI/ModelWindow/model_window.cpp \
        GUI/PlotDialog/plot_chart.cpp \
        GUI/PlotDialog/plot_chart_view.cpp \
        GUI/PlotDialog/plot_dialog.cpp \
        GUI/PlotDialog/select_models_dialog.cpp \
        Models/linear_demands_constant_costs.cpp \
        Models/linear_demands_linear_costs.cpp \
        Utils/algebra.cpp \
        Utils/column_vector.cpp \
        Utils/matrix.cpp \
        Utils/row_vector.cpp \
        main.cpp

HEADERS += \
    GUI/Common/base_table_view.h \
    GUI/CompareDialog/compare_table_data.h \
    GUI/CompareDialog/compare_table_view.h \
    GUI/MainWindow/load_model_widget.h \
    GUI/MainWindow/main_window.h \
    GUI/ModelWindow/MergeDialog/Helpers/firm_widget.h \
    GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.h \
    GUI/ModelWindow/MergeDialog/Helpers/product_list_item.h \
    GUI/ModelWindow/MergeDialog/merge_dialog.h \
    GUI/ModelWindow/MergeDialog/merge_widget.h \
    GUI/ModelWindow/model_table_data.h \
    GUI/ModelWindow/model_table_view.h \
    GUI/ModelWindow/model_window.h \
    GUI/PlotDialog/model_plot_data.h \
    GUI/PlotDialog/plot_chart.h \
    GUI/PlotDialog/plot_chart_view.h \
    GUI/PlotDialog/plot_dialog.h \
    GUI/PlotDialog/select_models_dialog.h \
    Models/linear_demands_constant_costs.h \
    Models/linear_demands_linear_costs.h \
    Models/model_factory.h \
    Models/model_interface.h \
    Models/model_type.h \
    Utils/algebra.h \
    Utils/column_vector.h \
    Utils/matrix.h \
    Utils/row_vector.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
