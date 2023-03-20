#include "openGlShader.h"

OpenGLShader::OpenGLShader() : program(new QOpenGLShaderProgram) {

}

void OpenGLShader::init() {
    initializeOpenGLFunctions();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs");
    program->link();
}

void OpenGLShader::drawElements(OpenGLVertexArray &va, OpenGLVertexBuffer &vb, OpenGLElementBuffer &eb, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 lightPos, glm::vec3 cameraPos) {
    program->bind();
    va.bind();
    vb.bind();
    glm::vec3 color = glm::vec3(1.0, 0.0, 1.0);
    glUniform3fv(glGetUniformLocation(program->programId(), "aColor"), 1, glm::value_ptr(color));
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection[0]));
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "view"), 1, GL_FALSE, glm::value_ptr(view[0]));
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "model"), 1, GL_FALSE, glm::value_ptr(model[0]));
    glUniform3fv(glGetUniformLocation(program->programId(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(program->programId(), "cameraPos"), 1, glm::value_ptr(cameraPos));
    eb.bind();
    glDrawElements(GL_TRIANGLES, (GLsizei) eb.mCount, GL_UNSIGNED_INT, nullptr);
}
