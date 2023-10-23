#include "openGlItem.h"

OpenGLItem::OpenGLItem() {

}

void OpenGLItem::setColor(const glm::vec3 &c) {
    color = c;
}

void OpenGLItem::setPosition(const glm::vec3 &pos) {
    mPos = pos;
}

void OpenGLItem::setAlpha(const float &a) {
    alpha = a;
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
/*
    The four corners of the equilateral pyramid:
    x,                      y,               z,
    x,                      y + r,           z,
    x + r * sin(60),        y + r * cos(60), z,
    x + r * sin(60) * 1/3,  y + r * cos(60), z + sqrt(r^2 - (r * sin(60) - (1/3) * r * sin(60))^2)
*/
    vertices.clear();
    // Push the cardinal angles to the vertices vector
    vertices.insert(vertices.end(), {   mPos.x,
                                        mPos.y,
                                        mPos.z});
    vertices.insert(vertices.end(), {   mPos.x,
                                        mPos.y + mSideLength,
                                        mPos.z});
    vertices.insert(vertices.end(), {   mPos.x + mSideLength * sinf(qDegreesToRadians(60.0f)),
                                        mPos.y + mSideLength * cosf(qDegreesToRadians(60.0f)),
                                        mPos.z});
    vertices.insert(vertices.end(), {   mPos.x + mSideLength * 0.5f * tanf(qDegreesToRadians(30.0f)),
                                        mPos.y + mSideLength * cosf(qDegreesToRadians(60.0f)),
                                        mPos.z + sqrtf(powf(mSideLength, 2) - powf((mSideLength * sinf(qDegreesToRadians(60.0))) - ((1.0f/3.0f) * (mSideLength * sinf(M_PI/3))), 2))});

    indices = {
        0, 1, 2,
        0, 1, 3,
        1, 2, 3,
        0, 2, 3
    };

    // Require midpoints for
    std::vector<float> midpoints;
    std::vector<float> temp;
    // 0 to 1
    temp = createMidpoint(0, 1);
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    // 0 to 2
    temp = createMidpoint(0, 2);
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    // 1 to 2
    temp = createMidpoint(1, 2);
    qDebug() << temp;
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    // 0 to 3
    temp = createMidpoint(0, 3);
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    // 1 to 3
    temp = createMidpoint(1, 3);
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    // 2 to 3
    temp = createMidpoint(2, 3);
    midpoints.insert(midpoints.end(), temp.begin(), temp.end());
    float angleStep = (70.553364148f) / (float) mResolution;
    float theta = qDegreesToRadians(210.0);
    float newSideLength = mSideLength * (sqrtf(3)/2);
    for(int i = 0; i < 3; i++) {
        theta -= qDegreesToRadians(120.0f);
        uint midpointIndex = vertices.size()/3;
        uint indicesCounter = midpointIndex + 1;
        glm::vec3 midPoint = {midpoints[i * 3], midpoints[(i * 3) + 1], midpoints[(i * 3) + 2]};
        vertices.insert(vertices.end(), {midPoint.x, midPoint.y, midPoint.z});
        for(int j = 1; j < mResolution + 1; j++) {
            float angle = qDegreesToRadians(90 - ((float) j * angleStep));
            float anglePrev = qDegreesToRadians(90 - ((float) (j - 1) * angleStep));
            vertices.insert(vertices.end(), {midPoint.x + (newSideLength * sinf(angle) * sinf(theta)),
                                             midPoint.y + (newSideLength * sinf(angle) * cosf(theta)),
                                             midPoint.z + (newSideLength * cosf(angle))});
            vertices.insert(vertices.end(), {midPoint.x + (newSideLength * sinf(anglePrev) * sinf(theta)),
                                             midPoint.y + (newSideLength * sinf(anglePrev) * cosf(theta)),
                                             midPoint.z + (newSideLength * cosf(anglePrev))});
            indices.insert(indices.end(), {midpointIndex, indicesCounter, indicesCounter + 1});
            indicesCounter += 2;
        }
    }
    float roll = 0.0f;
    float offsetAngle = qDegreesToRadians(90.0f + (70.553364148f/2.0f));
    theta -= qDegreesToRadians(30.0f);
    // Bottom edges need to have the curves added too
    for(int i = 3; i < 6; i++) {
        theta += qDegreesToRadians(120.0f);
        uint midpointIndex = vertices.size()/3;
        uint indicesCounter = midpointIndex + 1;
        glm::vec3 midPoint = {midpoints[i * 3], midpoints[(i * 3) + 1], midpoints[(i * 3) + 2]};
        vertices.insert(vertices.end(), {midPoint.x, midPoint.y, midPoint.z});
        for(int j = 1; j < mResolution + 1; j++) {
            float angle = qDegreesToRadians(90 - ((float) j * angleStep));
            float anglePrev = qDegreesToRadians(90 - ((float) (j - 1) * angleStep));
            vertices.insert(vertices.end(), {midPoint.x + (newSideLength * sinf(angle + offsetAngle) * sinf(theta)) + (newSideLength * cosf(qDegreesToRadians(35.264)) * cosf(qDegreesToRadians(90.0f + 30.0f + roll))),
                                             midPoint.y + (newSideLength * sinf(angle + offsetAngle) * cosf(theta)),
                                             midPoint.z + (newSideLength * cosf(angle + offsetAngle)) + (newSideLength * sinf(qDegreesToRadians(35.264)))});
            vertices.insert(vertices.end(), {midPoint.x + (newSideLength * sinf(anglePrev + offsetAngle) * sinf(theta)) + (newSideLength * cosf(qDegreesToRadians(35.264)) * cosf(qDegreesToRadians(90.0f + 30.0f + roll))),
                                             midPoint.y + (newSideLength * sinf(anglePrev + offsetAngle) * cosf(theta)),
                                             midPoint.z + (newSideLength * cosf(anglePrev + offsetAngle)) + (newSideLength * sinf(qDegreesToRadians(35.264)))});
            indices.insert(indices.end(), {midpointIndex, indicesCounter, indicesCounter + 1});
            indicesCounter += 2;
        }
    }
}

std::vector<float> OpenGLItemReuleaux::createMidpoint(int a, int b) {
    a *= 3;
    b *= 3;
    std::vector<float> aV(&vertices[a], &vertices[a + 3]);
    std::vector<float> bV(&vertices[b], &vertices[b + 3]);
    return {(aV[0] + bV[0])/2, (aV[1] + bV[1])/2, (aV[2] + bV[2])/2};
}
