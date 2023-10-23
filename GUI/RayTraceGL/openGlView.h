#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>

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
public slots:
    void setDimensions(const glm::vec3 &);
    void setFov(double);
private:
    GLenum mode = GL_FILL;
    double mFov;
    bool timerRunning = false;
//    QElapsedTimer eTimer;
    QTimer eTimer;
    OpenGLShader shader;
    QList<QSharedPointer<OpenGLItem>> scene;
    QList<QSharedPointer<OpenGLItem>> items;
    glm::vec3 mDimensions; // x: width; y: depth; z: height
    void createScene();
    void updateScene();
    qint64 time = 0;
    qint64 getTime();
};

#endif //OPENGLVIEW_H
