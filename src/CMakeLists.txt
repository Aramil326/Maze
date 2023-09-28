cmake_minimum_required(VERSION 3.5)

project(maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH /home/maslynem/Qt5.12.12/5.12.12/gcc_64/lib/cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cc

        view/maze_view/maze_scene.cc
        view/maze_view/maze_scene.h
        view/maze_view/maze_field.h
        view/maze_view/maze_field.cc
        view/maze_view/maze_scene.ui

        controller/controller.cc
        controller/controller.h

        model/maze_model/maze_model.h
        model/maze_model/maze_model.cc

        model/facade/facade.h
        model/facade/facade.cc

        model/model_loader/model_loader.h
        model/model_loader/model_loader.cc

        model/model_loader/error_load_type.h

        model/matrix/matrix.cc
        model/matrix/matrix.h
        model/maze_generator/maze_generator.cc
        model/maze_generator/maze_generator.h
        model/maze_solver/maze_solver.cc
        model/maze_solver/maze_solver.h

        model/maze_solver/error_solve_type.h)
add_executable(maze ${PROJECT_SOURCES} )

install(TARGETS maze
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets -lstdc++)
#target_link_libraries(maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets -lstdc++ -lgtest -lm)
