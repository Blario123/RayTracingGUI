#ifndef TORUS_H
#define TORUS_H

#include "../openGlItem.h"

class OpenGLItemTorus : public OpenGLItem {
public:
    explicit OpenGLItemTorus(const glm::vec3 &pos, const float &innerRadius, const float &outerRadius) {
        mPos = pos;
        mInnerRadius = innerRadius;
        mRadius = (outerRadius - innerRadius) / 2;

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
    };
    std::vector<float> createPoint(float phi, float theta) {
        return {mPos.x + (mInnerRadius * sinf(phi)) + (mRadius * sinf(phi) * sinf(theta)), mPos.y + (mInnerRadius * cosf(phi)) + (mRadius * cosf(phi) * sinf(theta)), mPos.z + (mRadius * cosf(theta))};
    };
    int mResolution = 40;
    float mInnerRadius;
    float mRadius;
};

#endif // TORUS_H
