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
};

class OpenGLItemSphere : public OpenGLItem {
public:
    explicit OpenGLItemSphere(double radius = 1.0);
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
    std::vector<float> vertices;
    glm::vec3 mDimensions;
};

class OpenGLItemReuleaux : public OpenGLItem {
public:
    explicit OpenGLItemReuleaux(double sideLength);
};

#endif //OPENGLITEM_H
