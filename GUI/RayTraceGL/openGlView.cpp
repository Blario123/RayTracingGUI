#include "openGlView.h"

OpenGLView::OpenGLView(QWidget *parent) : QOpenGLWidget(parent) {
    Q_INIT_RESOURCE(openGlResources);
    setFocusPolicy(Qt::StrongFocus);
}

void OpenGLView::initializeGL() {
    initializeOpenGLFunctions();
    shader.init();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 800);
}

void OpenGLView::paintGL() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(45.0), 1.0, 0.1, 200.0);
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 lightPos(20.0, 20.0, -10);
    glm::vec3 cameraPos(0.0);

    for(auto i: items) {
        shader.drawElements(i->va, i->vb, i->eb, projection, view, model, lightPos, cameraPos);
    }

    update();
}

void OpenGLView::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    qDebug() << "size =" << width << "," << height;
}

void OpenGLView::keyPressEvent(QKeyEvent *event) {
    QOpenGLWidget::keyPressEvent(event);
}