#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "openGlVertexArray.h"
#include "openGlVertexBuffer.h"
#include "openGlElementBuffer.h"

class OpenGLShader : protected QOpenGLFunctions_4_5_Core {
public:
    explicit OpenGLShader();
    void init();
    void drawElements(OpenGLVertexArray &va, OpenGLVertexBuffer &vb, OpenGLElementBuffer &eb, const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &model, const glm::vec3 &lightPos, const glm::vec3 &cameraPos);
private:
    QOpenGLShaderProgram *program;
};

#endif //OPENGLSHADER_H
