#include "openGlVertexArray.h"

OpenGLVertexArray::OpenGLVertexArray() {

}

OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteBuffers(1, &vao);
}

void OpenGLVertexArray::init() {
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &vao);
}

void OpenGLVertexArray::bind() {
    glBindVertexArray(vao);
}

void OpenGLVertexArray::addBuffer(OpenGLVertexBuffer &vb) {
    initializeOpenGLFunctions();
    bind();
    vb.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    uint error = glGetError();
    if(error) {
        // Print error
    }
}
