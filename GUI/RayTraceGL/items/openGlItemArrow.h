#ifndef ARROW_H
#define ARROW_H

#include "../openGlItem.h"

class OpenGLItemArrow : public OpenGLItem {
public:
    enum Orientation {
        X = 0,
        Y,
        Z
    };
    explicit OpenGLItemArrow(const glm::vec3 &pos, Orientation o) {
        mPos = pos;
        mOrientation = o;
        va.init();
        va.bind();
    
        createVertices();
    
        vb.init(vertices);
        va.addBuffer(vb);
        eb.init(indices);
    };  
private:
    void createVertices() {
        uint indicesCounter = 2;
        vertices.clear();
        float segmentAngle = (2.0f * M_PIf) / (float) mResolution;
        // Create two reference center points.
        vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f});
        vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f});
        // Set the orientation length center point.
        vertices[(1 * 3) + mOrientation] = mLength;
        for(int i = 1; i < mResolution + 1; i++) {
            float angle = segmentAngle * (float) i;
            float anglePrev = segmentAngle * (float) (i - 1);
            float theta = 0.0f;
            float phi = 0.0f;
            float x = 1.0f;
            float y = 1.0f;
            float z = 1.0f;
            switch(mOrientation) {
                case X:
                    phi = M_PI_2f;
                    x = 0.0f;
                    break;
                case Y:
                    theta = M_PI_2f;
                    phi = M_PI_2f;
                    y = 0.0f;
                    break;
                case Z:
                    z = 0.0f;
                    break;
            }
            vertices.insert(vertices.end(), {
                    mRadius * cosf(angle) * x,
                    mRadius * sinf(angle) * y,
                    mRadius * cosf(angle + theta) * z
//                    mRadius * sinf(angle) * cosf(phi)
            });
            vertices.insert(vertices.end(), {
                    mRadius * cosf(anglePrev) * x,
                    mRadius * sinf(anglePrev) * y,
                    mRadius * cosf(anglePrev + theta) * z
//                    (mRadius * cosf(anglePrev) * cosf(phi))
            });
            vertices.insert(vertices.end(), {
                    vertices[(1 * 3)] + vertices[(indicesCounter * 3)],
                    vertices[(1 * 3) + 1] + vertices[((indicesCounter * 3) + 1)],
                    vertices[(1 * 3) + 2] + vertices[((indicesCounter * 3) + 2)]
            });
            vertices.insert(vertices.end(), {
                    vertices[(1 * 3)] + vertices[((indicesCounter + 1) * 3)],
                    vertices[(1 * 3) + 1] + vertices[(((indicesCounter + 1) * 3) + 1)],
                    vertices[(1 * 3) + 2] + vertices[(((indicesCounter + 1) * 3) + 2)]
            });
            indices.insert(indices.end(), {0, indicesCounter, indicesCounter + 1});
            indices.insert(indices.end(), {1, indicesCounter + 2, indicesCounter +3});
            indices.insert(indices.end(), {indicesCounter, indicesCounter + 1, indicesCounter + 3});
            indices.insert(indices.end(), {indicesCounter + 2, indicesCounter + 3, indicesCounter});
            indicesCounter += 4;
        }

    };
    Orientation mOrientation;
    int mResolution = 10;
    float mLength = 0.5f;
    float mRadius = 0.001f;
};

#endif //ARROW_H
