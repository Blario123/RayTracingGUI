#include "openGlVertexBuffer.h"

OpenGLVertexBuffer::OpenGLVertexBuffer() {

}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &vbo);
}

void OpenGLVertexBuffer::init(const std::vector<float> &v) {
    initializeOpenGLFunctions();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(v.size() * sizeof(float)), &v.front(), GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void OpenGLVertexBuffer::update(const std::vector<float> &v) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(v.size() * sizeof(float)), &v.front(), GL_STATIC_DRAW);
}
