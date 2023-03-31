#include "openGlItem.h"

OpenGLItem::OpenGLItem() {

}

void OpenGLItem::setColor(const glm::vec3 &c) {
    color = c;
}

void OpenGLItem::setPosition(const glm::vec3 &pos) {
    mPos = pos;
}

OpenGLItemSphere::OpenGLItemSphere(const glm::vec3 &pos, float radius) {
    mPos = pos;
    mRadius = radius;

    va.init();
    va.bind();

    createVertices();

    vb.init(vertices);
    va.addBuffer(vb);
    eb.init(indices);
}

void OpenGLItemSphere::createVertices() {
    vertices.clear();
    uint indicesCounter = 0;
    for(int i = 2; i <= mResolution + 1; i++) {
        const float loopAngleHz = (2 * (float) M_PI) / (float)(mResolution + 1);
        float prevAngleHz = ((float) i - 1) * loopAngleHz;
        float angleHz = (float) i * loopAngleHz;
        vertices.insert(vertices.end(), {mPos.x, mPos.y, mPos.z + mRadius});
        indices.insert(indices.end(), {++indicesCounter, indicesCounter + 1, indicesCounter + 2});
        for(int j = 2; j <= (mResolution / 2); j++) {
            const float loopAngleVert = (2 * (float) M_PI) / (float)(mResolution + 1);
            float prevAngleVert = ((float) j - 1) * loopAngleVert;
            float angleVert = (float) j * loopAngleVert;

            std::vector<float> pos1 = createPoint(angleHz, angleVert);
            std::vector<float> pos2 = createPoint(angleHz, prevAngleVert);
            std::vector<float> pos3 = createPoint(prevAngleHz, angleVert);
            std::vector<float> pos4 = createPoint(prevAngleHz, prevAngleVert);

            qDebug() << "Pos1 = " << pos1;
            qDebug() << "Pos2 = " << pos2;
            qDebug() << "Pos3 = " << pos3;
            qDebug() << "Pos4 = " << pos4;

            vertices.insert(vertices.end(), pos1.begin(), pos1.end());
            indices.push_back(++indicesCounter);

            vertices.insert(vertices.end(), pos2.begin(), pos2.end());
            indices.push_back(++indicesCounter);

            vertices.insert(vertices.end(), pos3.begin(), pos3.end());
            indices.push_back(++indicesCounter);

            vertices.insert(vertices.end(), pos4.begin(), pos4.end());
            indices.insert(indices.end(), {++indicesCounter, indicesCounter - 2, indicesCounter - 3});
        }
        vertices.insert(vertices.end(), {mPos.x, mPos.y, mPos.z - mRadius});
        indices.insert(indices.end(), {indicesCounter - 2, indicesCounter - 3, ++indicesCounter});
        // printf("%f,%f,%f\n", mRadius * sinf(0.0) * sinf(prevAngleHz), mRadius * sinf(0.0) * cosf(prevAngleHz), -mRadius);
    }
}

std::vector<float> OpenGLItemSphere::createPoint(float theta, float phi) {
    return {mPos.x + (mRadius * sinf(theta) * sinf(phi)), mPos.y + (mRadius * sinf(theta) * cosf(phi)), mPos.z + (mRadius * cosf(theta))};
}

OpenGLItemTorus::OpenGLItemTorus(double innerRadius, double outerRadius) {

}

OpenGLItemCuboid::OpenGLItemCuboid(glm::vec3 pos, glm::vec3 dimensions) {
    mPos = pos;
    mDimensions = dimensions;
    va.init();
    va.bind();
    createVertices();

    indices = {
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
