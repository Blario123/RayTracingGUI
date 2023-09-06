#include "openGlShader.h"

OpenGLShader::OpenGLShader() : program(new QOpenGLShaderProgram) {

}

void OpenGLShader::init() {
    initializeOpenGLFunctions();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs");
    program->link();
}

void OpenGLShader::drawElements(OpenGLVertexArray &va, OpenGLVertexBuffer &vb, OpenGLElementBuffer &eb, glm::vec3 color, float alpha, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 lightPos, glm::vec3 cameraPos) {
    program->bind();
    va.bind();
    vb.bind();
    setVec3("aColor", color);
    setVec1("alpha", alpha);
    setMat4("projection", projection);
    setMat4("view", view);
    setMat4("model", model);
    setVec3("lightPos", lightPos);
    setVec3("cameraPos", cameraPos);
    eb.bind();
    glDrawElements(GL_TRIANGLES, (GLsizei) eb.mCount, GL_UNSIGNED_INT, nullptr);
}

void OpenGLShader::setVec1(const std::string &name, const float &v) {
//    glUniform1fv(glGetUniformLocation(program->programId(), name.c_str()), 1, glm::value_ptr(v));
    glUniform1f(glGetUniformLocation(program->programId(), name.c_str()), v);
}

void OpenGLShader::setVec3(const std::string &name, const glm::vec3 &v) {
    glUniform3fv(glGetUniformLocation(program->programId(), name.c_str()), 1, glm::value_ptr(v));
}

void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &v) {
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}
