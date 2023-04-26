#ifndef OPENGLITEM_H
#define OPENGLITEM_H

#include <vector>

#include <QOpenGLFunctions_3_3_Core>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "openGlVertexArray.h"
#include "openGlVertexBuffer.h"
#include "openGlElementBuffer.h"

#define EULER_M_CONST 0.5772156649015329

class OpenGLItem : protected QOpenGLFunctions_3_3_Core {
public:
    explicit OpenGLItem();
    OpenGLVertexArray va;
    OpenGLVertexBuffer vb;
    OpenGLElementBuffer eb;
    glm::vec3 color;
public slots:
    void setColor(const glm::vec3 &);
    virtual void setPosition(const glm::vec3 &);
protected:
    glm::vec3 mPos;
    std::vector<float> vertices;
    std::vector<uint> indices;
};

class OpenGLItemSphere : public OpenGLItem {
public:
    explicit OpenGLItemSphere(const glm::vec3 &, float radius = 0.5);
private:
    void createVertices();
    std::vector<float> createPoint(float, float);
    float mRadius;
    int mResolution = 40;
};

class OpenGLItemTorus : public OpenGLItem {
public:
    explicit OpenGLItemTorus(const glm::vec3 &, const float &, const float &);
private:
    void createVertices();
    std::vector<float> createPoint(float, float);
    int mResolution = 40;
    float mInnerRadius;
    float mRadius;
};

class OpenGLItemCuboid : public OpenGLItem {
public:
    explicit OpenGLItemCuboid(glm::vec3 pos, glm::vec3 dimensions);
public slots:
    void setPosition(const glm::vec3 &) override;
    void setDimensions(const glm::vec3 &);
private:
    void createVertices();
    glm::vec3 mDimensions;
};

class OpenGLItemReuleaux : public OpenGLItem {
public:
    explicit OpenGLItemReuleaux(const glm::vec3 &pos, const float &sideLength = 0.5);
private:
    void createVertices();
    glm::vec2 coordsFromPoint(const glm::vec2 &pos, const double &angle) const;
    float mSideLength;
    int mResolution = 4;
};

#endif //OPENGLITEM_H
