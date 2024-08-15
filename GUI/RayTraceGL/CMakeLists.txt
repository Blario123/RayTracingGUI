project(RayTraceGL)

set(CMAKE_AUTORCC ON)

set(SRC
        openGlView.cpp
        openGlShader.cpp
        openGlVertexArray.cpp
        openGlVertexBuffer.cpp
        openGlElementBuffer.cpp
        openGlItem.cpp
        items/openGlItemArrow.h
        items/openGlItemCuboid.h
        items/openGlItemReuleaux.h
        items/openGlItemSphere.h
        items/openGlItemReuleaux.h)

set(TESTS
        test/main.cpp)

qt_add_resources(RSC openGlResources.qrc)

add_library(RayTraceGL ${SRC} ${RSC})
target_link_libraries(RayTraceGL Qt::Core Qt::Widgets Qt::OpenGLWidgets)

add_executable(RayTraceGLTest ${TESTS})
target_link_libraries(RayTraceGLTest RayTraceGL)
