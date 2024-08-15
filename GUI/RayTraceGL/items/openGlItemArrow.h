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
        float theta = 0.0f;
        float phi = 0.0f;
        vertices.clear();
        float segmentAngle = (2.0f * M_PI) / (float) mResolution;
        // Create two reference center points.
        vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f});
        vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f});
        // Set the orientation length center point.
        vertices[(1 * 3) + mOrientation] = mLength;
        for(int i = 1; i < mResolution + 1; i++) {
            float angle = segmentAngle * i;
            float anglePrev = segmentAngle * i - 1;
            switch(mOrientation) {
                case X:
                    phi = M_PI_2f;
                    break;
                case Y:
                    theta = M_PI_2f;
                    phi = M_PI_2f;
                    break;
                case Z:
                    break;
            }
            vertices.insert(vertices.end(), {
                    mRadius * cosf(angle),
                    mRadius * sinf(angle),
                    0
            });
            vertices.insert(vertices.end(), {
                    mRadius * cosf(anglePrev),
                    mRadius * sinf(anglePrev),
                    0
            });
            vertices.insert(vertices.end(), {
                    vertices[(1 * 3)] + vertices[(indicesCounter * 3)],
                    vertices[(1 * 3) + 1] + vertices[((indicesCounter * 3) + 1)],
                    vertices[(1 * 3) + 2]
            });
            vertices.insert(vertices.end(), {
                    vertices[(1 * 3)] + vertices[((indicesCounter + 1) * 3)],
                    vertices[(1 * 3) + 1] + vertices[(((indicesCounter + 1) * 3) + 1)],
                    vertices[(1 * 3) + 2]
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
    float mLength = 2.0f;
    float mRadius = 0.01f;
};

#endif //ARROW_H
