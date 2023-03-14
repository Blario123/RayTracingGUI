#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include <QOpenGLFunctions_4_5_Core>

#include "openGlVertexBuffer.h"

class OpenGLVertexArray : protected QOpenGLFunctions_4_5_Core {
public:
    explicit OpenGLVertexArray();
    ~OpenGLVertexArray() override;
    void init();
    void bind();
    void addBuffer(OpenGLVertexBuffer &);
private:
    GLuint vao;
};

#endif //OPENGLVERTEXARRAY_H
