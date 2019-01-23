cmake_minimum_required (VERSION 2.6)
project (Merger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "E:\\Qt\\5.11.2\\mingw53_32\\" )
else()
    set(CMAKE_PREFIX_PATH "/opt/Qt/5.11.2/gcc_64/" )
endif()

find_package(Qt5Widgets CONFIG REQUIRED)

set(SOURCES
    GUI/MainWindow/load_model_widget.cpp
    GUI/MainWindow/load_model_widget.h
    GUI/MainWindow/main_window.cpp
    GUI/MainWindow/main_window.h
    GUI/ModelWindow/MergeDialog/Helpers/firm_widget.cpp
    GUI/ModelWindow/MergeDialog/Helpers/firm_widget.h
    GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.cpp
    GUI/ModelWindow/MergeDialog/Helpers/multi_product_firms_widget.h
    GUI/ModelWindow/MergeDialog/merge_dialog.cpp
    GUI/ModelWindow/MergeDialog/merge_dialog.h
    GUI/ModelWindow/MergeDialog/merge_widget.cpp
    GUI/ModelWindow/MergeDialog/merge_widget.h
    GUI/ModelWindow/model_table_data.cpp
    GUI/ModelWindow/model_table_data.h
    GUI/ModelWindow/model_table_view.cpp
    GUI/ModelWindow/model_table_view.h
    GUI/ModelWindow/model_window.cpp
    GUI/ModelWindow/model_window.h
    Models/linear_demands_constant_costs.cpp
    Models/linear_demands_constant_costs.h
    Models/model_factory.h
    Models/model_interface.h
    Models/model_type.h
    Utils/algebra.cpp
    Utils/algebra.h
    Utils/column_vector.cpp
    Utils/column_vector.h
    Utils/matrix.cpp
    Utils/matrix.h
    Utils/row_vector.cpp
    Utils/row_vector.h
    main.cpp)

add_executable(Merger ${SOURCES})
target_link_libraries(Merger Qt5::Widgets)

