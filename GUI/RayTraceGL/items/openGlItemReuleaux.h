#ifndef REULEAUX_H
#define REULEAUX_H

#include "../openGlItem.h"

class OpenGLItemReuleaux : public OpenGLItem {
public:
    explicit OpenGLItemReuleaux(const glm::vec3 &pos, const float &sideLength = 0.5) {
        mPos = pos;
        mSideLength = sideLength;
    
        va.init();
        va.bind();

        createVertices();

        vb.init(vertices);
        va.addBuffer(vb);
        eb.init(indices);
    };
private:
    void createVertices() {
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
    };
    std::vector<float> createMidpoint(int a, int b) {
        a *= 3;
        b *= 3;
        std::vector<float> aV(&vertices[a], &vertices[a + 3]);
        std::vector<float> bV(&vertices[b], &vertices[b + 3]);
        return {(aV[0] + bV[0])/2, (aV[1] + bV[1])/2, (aV[2] + bV[2])/2};
    };
    float mSideLength;
    int mResolution = 2;
};

#endif // REULEAUX_H
