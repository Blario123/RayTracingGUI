#include "openGlItem.h"

OpenGLItem::OpenGLItem() {

}

void OpenGLItem::setColor(const glm::vec3 &c) {
    color = c;
}

void OpenGLItem::setPosition(const glm::vec3 &pos) {
    mPos = pos;
}

OpenGLItemSphere::OpenGLItemSphere(double radius) {

}

OpenGLItemTorus::OpenGLItemTorus(double innerRadius, double outerRadius) {

}

OpenGLItemCuboid::OpenGLItemCuboid(glm::vec3 pos, glm::vec3 dimensions) {
    mPos = pos;
    mDimensions = dimensions;
    va.init();
    va.bind();
    createVertices();

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
    va.addBuffer(vb);
    eb.init(indices);
}

void OpenGLItemCuboid::setPosition(const glm::vec3 &pos) {
    mPos = pos;
    createVertices();
    vb.update(vertices);
}

void OpenGLItemCuboid::setDimensions(const glm::vec3 &dim) {
    mDimensions = dim;
    createVertices();
    vb.update(vertices);
}

void OpenGLItemCuboid::createVertices() {
    vertices = {
        mPos.x,                 mPos.y,                  mPos.z,
        mPos.x + mDimensions.x, mPos.y,                  mPos.z,
        mPos.x + mDimensions.x, mPos.y + mDimensions.y,  mPos.z,
        mPos.x,                 mPos.y + mDimensions.y,  mPos.z,
        mPos.x,                 mPos.y,                  mPos.z + mDimensions.z,
        mPos.x + mDimensions.x, mPos.y,                  mPos.z + mDimensions.z,
        mPos.x + mDimensions.x, mPos.y + mDimensions.y,  mPos.z + mDimensions.z,
        mPos.x,                 mPos.y + mDimensions.y,  mPos.z + mDimensions.z
    };
}

OpenGLItemReuleaux::OpenGLItemReuleaux(double sideLength) {

}
