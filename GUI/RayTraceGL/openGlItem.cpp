#include "openGlItem.h"

OpenGLItem::OpenGLItem() {
    // initializeOpenGLFunctions();
}


void OpenGLItem::init() {
    va.init();
    va.bind();
    glm::vec3 size(1.0, 1.0, 1.0);
    std::vector<float> vertices = {
        0.0, 0.0, 0.0,
        size.x, 0.0, 0.0,
        size.x, size.y, 0.0,
        0.0, size.y, 0,
        0.0, 0.0, size.z,
        size.x, 0.0, size.z,
        size.x, size.y, size.z,
        0.0, size.y, size.z
    };

    std::vector<uint> indices = {
        0, 1, 2,
        2, 3, 0,
        0, 3, 4,
        4, 3, 7,
        7, 4, 6,
        6, 4, 5,
        5, 6, 2,
        2, 5, 1,
        1, 0, 4,
        4, 5, 1,
        3, 7, 2,
        2, 6, 7
    };
    vb.init(vertices);
    eb.init(indices);
    va.addBuffer(vb);
}

OpenGLItemSphere::OpenGLItemSphere(double radius) {
    init();
}

OpenGLItemTorus::OpenGLItemTorus(double innerRadius, double outerRadius) {

}

OpenGLItemCuboid::OpenGLItemCuboid(glm::vec3 dimensions) {

}

OpenGLItemReuleaux::OpenGLItemReuleaux(double sideLength) {

}
