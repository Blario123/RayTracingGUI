#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "openGlShader.h"
#include "openGlItem.h"

class OpenGLView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT
public:
    explicit OpenGLView(QWidget *parent = nullptr);
    ~OpenGLView() override = default;
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;
    void keyPressEvent(QKeyEvent *) override;
private:
    OpenGLShader shader;
    QList<QSharedPointer<OpenGLItem>> items;
    // VertexArray
    // VertexBuffer
    // ElementBuffer
    // Model?
};

#endif //OPENGLVIEW_H
