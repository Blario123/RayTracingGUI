#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "openGlVertexArray.h"
#include "openGlVertexBuffer.h"
#include "openGlElementBuffer.h"

class OpenGLShader : protected QOpenGLFunctions_3_3_Core {
public:
    explicit OpenGLShader();
    void init();
    void drawElements(OpenGLVertexArray &va, OpenGLVertexBuffer &vb, OpenGLElementBuffer &eb, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 lightPos, glm::vec3 cameraPos);
private:
    QOpenGLShaderProgram *program;
    void setVec3(const std::string &, const glm::vec3 &);
    void setMat4(const std::string &, const glm::mat4 &);
};

#endif //OPENGLSHADER_H
