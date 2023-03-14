#ifndef OPENGLITEM_H
#define OPENGLITEM_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "openGlVertexArray.h"
#include "openGlVertexBuffer.h"
#include "openGlElementBuffer.h"

class OpenGLItem {
public:
    explicit OpenGLItem();
    OpenGLVertexArray va;
    OpenGLVertexBuffer vb;
    OpenGLElementBuffer eb;

};

class OpenGLItemSphere : public OpenGLItem {
public:
    explicit OpenGLItemSphere(double radius);
};

class OpenGLItemTorus : public OpenGLItem {
public:
    explicit OpenGLItemTorus(double innerRadius, double outerRadius);
};

class OpenGLItemCuboid : public OpenGLItem {
public:
    explicit OpenGLItemCuboid(glm::vec3 dimensions);
};

class OpenGLItemReuleaux : public OpenGLItem {
public:
    explicit OpenGLItemReuleaux(double sideLength);
};

#endif //OPENGLITEM_H
