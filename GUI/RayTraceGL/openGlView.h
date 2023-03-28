#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QElapsedTimer>
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
    double mFov;
    QElapsedTimer eTimer;
    OpenGLShader shader;
    QList<QSharedPointer<OpenGLItem>> scene;
    QList<QSharedPointer<OpenGLItem>> items;
    glm::vec3 mDimensions; // x: width; y: depth; z: height
    void createScene();
    void updateScene();
};

#endif //OPENGLVIEW_H
