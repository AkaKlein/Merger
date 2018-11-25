cmake_minimum_required (VERSION 2.6)
project (Merger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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
    GUI/main_window.cpp
    GUI/main_window.h
    Models/linear_demands_constant_costs.cpp
    Models/linear_demands_constant_costs.h
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

