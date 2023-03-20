#ifndef OPENGLELEMENTBUFFER_H
#define OPENGLELEMENTBUFFER_H

#include <QOpenGLFunctions_3_3_Core>

class OpenGLElementBuffer : protected QOpenGLFunctions_3_3_Core {
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
