project(GUI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        OpenGLWidgets
        REQUIRED)

set(SRC
        gui.cpp
        bottomPanel.cpp
        brdfItemTree.cpp
        fileBar.cpp
        itemTree.cpp
        sidePanel.cpp
        statusBar.cpp
        view.cpp)

set(HDR
        # GUI elements
        gui.h
        bottomPanel.h
        brdfItemTree.h
        brdfItemDialog.h
        fileBar.h
        itemTree.h
        sidePanel.h
        statusBar.h
        view.h
        # Ray-tracing elements
        brdf.h)

include_directories(../ray-tracer/include)

add_library(GUI ${SRC} ${HDR})

target_link_libraries(GUI Qt::Core Qt::Gui Qt::Widgets Qt::OpenGL Qt::OpenGLWidgets)