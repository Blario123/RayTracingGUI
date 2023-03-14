#ifndef OPENGLELEMENTBUFFER_H
#define OPENGLELEMENTBUFFER_H

#include <QOpenGLFunctions_4_5_Core>

class OpenGLElementBuffer : protected QOpenGLFunctions_4_5_Core {
public:
    explicit OpenGLElementBuffer();
    ~OpenGLElementBuffer() override;
    void init(const std::vector<uint> &);
    void bind();
    int mCount;
private:
    GLuint ebo;
};

#endif //OPENGLELEMENTBUFFER_H
