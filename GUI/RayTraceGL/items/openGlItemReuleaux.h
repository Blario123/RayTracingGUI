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
    // TODO: Remove after testing
    void setEulerAngles(int x, int y, int z) {
        e_X = glm::radians((float) x / 10.0f);
        e_Y = glm::radians((float) y / 10.0f);
        e_Z = glm::radians((float) z / 10.0f);
        createVertices();
        vb.update(vertices);
    };
private:
    void createVertices() {
        if((mResolution % 2) != 0) {
            mResolution++;
        }
        /*
            The four corners of the equilateral pyramid:
            x,                      y,               z,
            x,                      y + r,           z,
            x + r * sin(60),        y + r * cos(60), z,
            x + r * sin(60) * 1/3,  y + r * cos(60), z + sqrt(r^2 - (r * sin(60) - (1/3) * r * sin(60))^2)
*/
        indices.clear();
        vertices.clear();
        // Push the cardinal angles to the vertices vector
        vertices.insert(vertices.end(), {
            mPos.x,
            mPos.y,
            mPos.z
        });
        vertices.insert(vertices.end(), {
            mPos.x,
            mPos.y + mSideLength,
            mPos.z
        });
        vertices.insert(vertices.end(), {
            mPos.x + mSideLength * sinf(qDegreesToRadians(60.0f)),
            mPos.y + mSideLength * cosf(qDegreesToRadians(60.0f)),
            mPos.z
        });
        vertices.insert(vertices.end(), {
            mPos.x + mSideLength * 0.5f * tanf(qDegreesToRadians(30.0f)),
            mPos.y + mSideLength * cosf(qDegreesToRadians(60.0f)),
            mPos.z + sqrtf(powf(mSideLength, 2) - powf((mSideLength * sinf(qDegreesToRadians(60.0))) - ((1.0f/3.0f) * (mSideLength * sinf(M_PI/3))), 2))
        });

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
        midpoints.insert(midpoints.end(), temp.begin(), temp.end());
        //
        // Vertex Ribs
        //
        float angleStep = (60.0f) / (float) mResolution;
        float theta = qDegreesToRadians(210.0);
        float elevOffsetAngle = 10.553364148f / 2.0f;
        for(int i = 0; i < 3; i++) {
            theta -= qDegreesToRadians(120.0f);
            uint midpointIndex = vertices.size()/3;
            uint indicesCounter = midpointIndex + 1;
            int offsetVertexPos;
            switch(i) {
                case 0:
                    offsetVertexPos = 2;
                    break;
                case 1:
                    offsetVertexPos = 1;
                    break;
                case 2:
                    offsetVertexPos = 0;
                    break;
            }
            glm::vec3 offset;
            glm::vec3 midPoint; 
            for(int j = 1; j < mResolution + 1; j++) {
                float angle = qDegreesToRadians(90 - ((float) j * angleStep) - elevOffsetAngle);
                float anglePrev = qDegreesToRadians(90 - ((float) (j - 1) * angleStep) - elevOffsetAngle);

                glm::vec4 p1 = {
                    (mSideLength * sinf(angle) * sinf(theta)),
                    (mSideLength * sinf(angle) * cosf(theta)),
                    (mSideLength * cosf(angle)),
                    1.0f
                };


                glm::vec4 p2 = {
                    (mSideLength * sinf(anglePrev) * sinf(theta)),
                    (mSideLength * sinf(anglePrev) * cosf(theta)),
                    (mSideLength * cosf(anglePrev)),
                    1.0f
                };

                if(j == 1) {
                    offset = {
                        (p2.x + midpoints[i * 3]) - vertices[(offsetVertexPos * 3)],
                        (p2.y + midpoints[(i * 3) + 1]) - vertices[(offsetVertexPos * 3) + 1],
                        (p2.z + midpoints[(i * 3) + 2]) - vertices[(offsetVertexPos * 3) + 2]
                    };
                    midpoints[i * 3] -= offset.x;
                    midpoints[(i * 3) + 1] -= offset.y;
                    midpoints[(i * 3) + 2] -= offset.z;
                    midPoint = {midpoints[i * 3], midpoints[(i * 3) + 1], midpoints[(i * 3) + 2]};
                    vertices.insert(vertices.end(), {midPoint.x, midPoint.y, midPoint.z});
                }
                vertices.insert(vertices.end(), {midPoint.x + p1.x, midPoint.y + p1.y, midPoint.z + p1.z});
                if(j == (mResolution / 2)) {
                    midpoints.insert(midpoints.end(), vertices.end() - 3, vertices.end());
                }
                vertices.insert(vertices.end(), {midPoint.x + p2.x, midPoint.y + p2.y, midPoint.z + p2.z});
                indices.insert(indices.end(), {midpointIndex, indicesCounter, indicesCounter + 1});
                indicesCounter += 2;
            }
        }
        // Bottom edges need to have the curves added too
        for(int i = 3; i < 6; i++) {
            uint midpointIndex = vertices.size()/3;
            uint indicesCounter = midpointIndex + 1;
            glm::vec3 midPoint = {midpoints[i * 3], midpoints[(i * 3) + 1], midpoints[(i * 3) + 2]};
            vertices.insert(vertices.end(), {midPoint.x, midPoint.y, midPoint.z});
            for(int j = 1; j < mResolution + 1; j++) {
                float angle = qDegreesToRadians(90 - ((float) j * angleStep));
                float anglePrev = qDegreesToRadians(90 - ((float) (j - 1) * angleStep));
                float phi = (M_PI_2f / 3.0f);
                glm::vec4 p1 = {
                    (mSideLength * sinf(theta + angle) * cosf(phi)),
                    (mSideLength * cosf(theta + angle) * cosf(phi)),
                    (mSideLength * sinf(-phi)),
                    1.0f
                };

                glm::vec4 p2 = {
                    (mSideLength * sinf(theta + anglePrev) * cosf(phi)),
                    (mSideLength * cosf(theta + anglePrev) * cosf(phi)),
                    (mSideLength * sinf(-phi)),
                    1.0f
                };

                vertices.insert(vertices.end(), {midPoint.x + p1.x, midPoint.y + p1.y, midPoint.z + p1.z});
                vertices.insert(vertices.end(), {midPoint.x + p2.x, midPoint.y + p2.y, midPoint.z + p2.z});
                indices.insert(indices.end(), {midpointIndex, indicesCounter, indicesCounter + 1});
                indicesCounter += 2;
            }
            theta -= (2.0f * M_PIf) / 3.0f;
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
    int mResolution = 10;
    // TODO: Delete after testing
    float e_X = 0.0f;
    float e_Y = 0.0f;
    float e_Z = 0.0f;
};

#endif // REULEAUX_H
