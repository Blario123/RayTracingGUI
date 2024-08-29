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
    float alpha = 1.0f;
public slots:
    void setColor(const glm::vec3 &);
    virtual void setPosition(const glm::vec3 &);
    void setAlpha(const float &);
protected:
    glm::vec3 mPos;
    std::vector<float> vertices;
    std::vector<uint> indices;
    glm::vec3 getPoint(int index);
};

#endif //OPENGLITEM_H
