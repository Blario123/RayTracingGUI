#ifndef SPHERE_H
#define SPHERE_H

#include "../openGlItem.h"

class OpenGLItemSphere : public OpenGLItem {
public:
    explicit OpenGLItemSphere(const glm::vec3 &pos, float radius = 0.5) {
        mPos = pos;
        mRadius = radius;
        va.init();
        va.bind();

        createVertices();

        vb.init(vertices);
        va.addBuffer(vb);
        eb.init(indices);
    };
private:
    void createVertices() {
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

                std::vector<float> pos = createPoint(prevAngleHz, prevAngleVert);

                vertices.insert(vertices.end(), pos.begin(), pos.end());
                indices.push_back(indicesCounter);
                indicesCounter++;

                pos = createPoint(angleHz, prevAngleVert);

                vertices.insert(vertices.end(), pos.begin(), pos.end());
                indices.push_back(indicesCounter);
                indicesCounter++;

                pos = createPoint(angleHz, angleVert);

                vertices.insert(vertices.end(), pos.begin(), pos.end());
                indices.push_back(indicesCounter);
                indicesCounter++;

                pos = createPoint(prevAngleHz, angleVert);

                vertices.insert(vertices.end(), pos.begin(), pos.end());
                indices.insert(indices.end(), {indicesCounter - 2, indicesCounter - 1, indicesCounter});
                indicesCounter++;

                pos.clear();
            }
            vertices.insert(vertices.end(), {mPos.x, mPos.y, mPos.z - mRadius});
            indices.insert(indices.end(), {indicesCounter - 2, indicesCounter - 1, indicesCounter});
            indicesCounter++;
        }
    };
    std::vector<float> createPoint(float phi, float theta) {
        return {mPos.x + (mRadius * sinf(theta) * sinf(phi)), mPos.y + (mRadius * sinf(theta) * cosf(phi)), mPos.z + (mRadius * cosf(theta))};
    };
    float mRadius;
    int mResolution = 40;
};


#endif // SPHERE_H
