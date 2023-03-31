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
    int mResolution = 20;
};

class OpenGLItemTorus : public OpenGLItem {
public:
    explicit OpenGLItemTorus(double innerRadius, double outerRadius);
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
    explicit OpenGLItemReuleaux(double sideLength);
};

#endif //OPENGLITEM_H
