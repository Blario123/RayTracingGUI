#include "openGlElementBuffer.h"

OpenGLElementBuffer::OpenGLElementBuffer() {

}

OpenGLElementBuffer::~OpenGLElementBuffer() {
    glDeleteBuffers(1, &ebo);
}

void OpenGLElementBuffer::init(const std::vector<uint> &indices) {
    mCount = indices.size();
    initializeOpenGLFunctions();
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(indices.size() * sizeof(float)), &indices.front(), GL_STATIC_DRAW);
}

void OpenGLElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
