#include "openGlItem.h"

OpenGLItem::OpenGLItem() {

}

void OpenGLItem::setColor(const glm::vec3 &c) {
    color = c;
}

OpenGLItemSphere::OpenGLItemSphere(double radius) {

}

OpenGLItemTorus::OpenGLItemTorus(double innerRadius, double outerRadius) {

}

OpenGLItemCuboid::OpenGLItemCuboid(glm::vec3 pos, glm::vec3 dimensions) {
    va.init();
    va.bind();
    std::vector<float> vertices = {
        pos.x,                  pos.y,                  pos.z,
        pos.x + dimensions.x,   pos.y,                  pos.z,
        pos.x + dimensions.x,   pos.y + dimensions.y,   pos.z,
        pos.x,                  pos.y + dimensions.y,   pos.z,
        pos.x,                  pos.y,                  pos.z + dimensions.z,
        pos.x + dimensions.x,   pos.y,                  pos.z + dimensions.z,
        pos.x + dimensions.x,   pos.y + dimensions.y,   pos.z + dimensions.z,
        pos.x,                  pos.y + dimensions.y,   pos.z + dimensions.z
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

OpenGLItemReuleaux::OpenGLItemReuleaux(double sideLength) {

}
