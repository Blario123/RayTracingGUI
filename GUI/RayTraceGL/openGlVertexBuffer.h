#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H

#include <QOpenGLFunctions_3_3_Core>

class OpenGLVertexBuffer : protected QOpenGLFunctions_3_3_Core {
public:
    explicit OpenGLVertexBuffer();
    ~OpenGLVertexBuffer() override;
    void init(const std::vector<float> &);
    void bind();
    void update(const std::vector<float> &);
private:
    GLuint vbo;
};

#endif //OPENGLVERTEXBUFFER_H
