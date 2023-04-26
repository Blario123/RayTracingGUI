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
    for(int i = 1; i <= mResolution + 1; i++) {
        const float loopAngleHz = (2 * (float) M_PI) / (float)(mResolution + 1);
        float prevAngleHz = ((float) i - 1) * loopAngleHz;
        float angleHz = (float) i * loopAngleHz;
        vertices.insert(vertices.end(), {mPos.x, mPos.y, mPos.z + mRadius});
        indices.insert(indices.end(), {indicesCounter, indicesCounter + 1, indicesCounter + 2});
        indicesCounter++;
        for(int j = 1; j <= (mResolution / 2); j++) {
            const float loopAngleVert = (2 * (float) M_PI) / (float)(mResolution + 1);
            float prevAngleVert = ((float) j - 1) * loopAngleVert;
            float angleVert = (float) j * loopAngleVert;

            std::vector<float> pos1 = createPoint(prevAngleHz, prevAngleVert);
            std::vector<float> pos2 = createPoint(angleHz, prevAngleVert);
            std::vector<float> pos3 = createPoint(angleHz, angleVert);
            std::vector<float> pos4 = createPoint(prevAngleHz, angleVert);

            vertices.insert(vertices.end(), pos1.begin(), pos1.end());
            indices.push_back(indicesCounter);
            indicesCounter++;

            vertices.insert(vertices.end(), pos2.begin(), pos2.end());
            indices.push_back(indicesCounter);
            indicesCounter++;

            vertices.insert(vertices.end(), pos3.begin(), pos3.end());
            indicesCounter++;
            indices.push_back(indicesCounter);

            vertices.insert(vertices.end(), pos4.begin(), pos4.end());
            indices.insert(indices.end(), {indicesCounter - 2, indicesCounter - 1, indicesCounter});
            indicesCounter++;
        }
        vertices.insert(vertices.end(), {mPos.x, mPos.y, mPos.z - mRadius});
        indices.insert(indices.end(), {indicesCounter - 2, indicesCounter - 1, indicesCounter});
        indicesCounter++;
    }
}

std::vector<float> OpenGLItemSphere::createPoint(float phi, float theta) {
    return {mPos.x + (mRadius * sinf(theta) * sinf(phi)), mPos.y + (mRadius * sinf(theta) * cosf(phi)), mPos.z + (mRadius * cosf(theta))};
}

OpenGLItemTorus::OpenGLItemTorus(const glm::vec3 &pos, const float &innerRadius, const float &outerRadius) {
    mPos = pos;
    mInnerRadius = innerRadius;
    mRadius = (outerRadius - innerRadius) / 2;

    va.init();
    va.bind();

    createVertices();

    vb.init(vertices);
    va.addBuffer(vb);
    eb.init(indices);
}

void OpenGLItemTorus::createVertices() {
    vertices.clear();
    uint indicesCounter = 0;
    for(int i = 1; i <= mResolution + 1; i++) {
        float loopAngleHz = (2 * (float) M_PI) / ((float) mResolution + 1);
        float angleHz = (float) i * loopAngleHz;
        float prevAngleHz = ((float) i - 1) * loopAngleHz;
        for(int j = 1; j <= mResolution; j++) {
            float loopAngleVert = (2 * (float) M_PI) / ((float) mResolution + 1);
            float angleVert = (float) j * loopAngleVert;
            float prevAngleVert = ((float) j - 1) * loopAngleVert;

            std::vector<float> pos1 = createPoint(angleHz, prevAngleVert);
            std::vector<float> pos2 = createPoint(prevAngleHz, prevAngleVert);
            std::vector<float> pos3 = createPoint(angleHz, angleVert);
            std::vector<float> pos4 = createPoint(prevAngleHz, angleVert);

            vertices.insert(vertices.end(), pos1.begin(), pos1.end());
            indices.push_back(indicesCounter);
            indicesCounter++;

            vertices.insert(vertices.end(), pos2.begin(), pos2.end());
            indices.push_back(indicesCounter);
            indicesCounter++;

            vertices.insert(vertices.end(), pos3.begin(), pos3.end());
            indices.push_back(indicesCounter);
            indicesCounter++;

            vertices.insert(vertices.end(), pos4.begin(), pos4.end());
            indices.insert(indices.end(), {indicesCounter, indicesCounter - 1, indicesCounter - 2});
            indicesCounter++;
        }
    }
}

std::vector<float> OpenGLItemTorus::createPoint(float phi, float theta) {
    return {mPos.x + (mInnerRadius * sinf(phi)) + (mRadius * sinf(phi) * sinf(theta)), mPos.y + (mInnerRadius * cosf(phi)) + (mRadius * cosf(phi) * sinf(theta)), mPos.z + (mRadius * cosf(theta))};
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

OpenGLItemReuleaux::OpenGLItemReuleaux(const glm::vec3 &pos, const float &sideLength) {
    mPos = pos;
    mSideLength = sideLength;

    va.init();
    va.bind();

    createVertices();

    vb.init(vertices);
    va.addBuffer(vb);
    eb.init(indices);
}

void OpenGLItemReuleaux::createVertices() {
    vertices.clear();
    uint indicesCounter = 0;
    // Bottom face
    // Split the face into three segments. These are then divided into mResolution chunks.
    for(int i = 0; i < 3; i++) {
        double startAngle = i * (2 * M_PI / 3);
        glm::vec2 arcCenterCoords = {mPos.x + (mSideLength * EULER_M_CONST) * sin(startAngle - M_PI), mPos.y + (mSideLength * EULER_M_CONST) * cos(startAngle - M_PI)};
        // Horizontal sectioning
        for(int j = 1; j <= mResolution; j++) {
            double arcDiv = (M_PI/3.0) / mResolution;
            double angle = startAngle + arcDiv * (float) j;
            double prevAngle = startAngle + arcDiv * ((float) j - 1);
            glm::vec2 pos = coordsFromPoint(arcCenterCoords, prevAngle);
//            qDebug() << pos.x << "," << pos.y;
            // Forward sections
            for(int k = 0; k < mResolution; k++) {

            }
        }
    }
}

glm::vec2 OpenGLItemReuleaux::coordsFromPoint(const glm::vec2 &pos, const double &angle) const {
    return {pos.x + (mSideLength * sin(angle - (M_PI/6.0))), pos.y + (mSideLength * cos(angle - (M_PI/6.0)))};
}
