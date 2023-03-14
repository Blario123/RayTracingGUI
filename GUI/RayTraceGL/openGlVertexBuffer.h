#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H

#include <QOpenGLFunctions_4_5_Core>

class OpenGLVertexBuffer : protected QOpenGLFunctions_4_5_Core {
public:
    explicit OpenGLVertexBuffer();
    ~OpenGLVertexBuffer() override;
    void init(const std::vector<float> &);
    void bind();
private:
    GLuint vbo;
};

#endif //OPENGLVERTEXBUFFER_H
