#include "openGlView.h"

OpenGLView::OpenGLView(QWidget *parent) : QOpenGLWidget(parent) {
    Q_INIT_RESOURCE(openGlResources);
    setFocusPolicy(Qt::StrongFocus);
    eTimer.start();
    setFixedSize(1920, 1080);
}

void OpenGLView::initializeGL() {
    makeCurrent();
    initializeOpenGLFunctions();
    shader.init();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 800);

    float width = 1.0;
    float depth = 3.0;
    float height = 1.0;

    QSharedPointer<OpenGLItem> topWall(new OpenGLItemCuboid(glm::vec3(0.0, 0.0, height), glm::vec3(width, depth, 0.0)));
    QSharedPointer<OpenGLItem> bottomWall(new OpenGLItemCuboid(glm::vec3(0.0, 0.0, 0.0), glm::vec3(width, depth, 0.0)));
    QSharedPointer<OpenGLItem> leftWall(new OpenGLItemCuboid(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, depth, height)));
    QSharedPointer<OpenGLItem> rightWall(new OpenGLItemCuboid(glm::vec3(width, 0.0, 0.0), glm::vec3(0.0, depth, height)));
    QSharedPointer<OpenGLItem> backWall(new OpenGLItemCuboid(glm::vec3(0.0, depth, 0.0), glm::vec3(width, 0.0, height)));
    QSharedPointer<OpenGLItem> cube(new OpenGLItemCuboid(glm::vec3(0.1, 0.1, 0.0), glm::vec3(0.2)));
    topWall->setColor(glm::vec3(1.0)); // White
    bottomWall->setColor(glm::vec3(0.2)); // Dark Gray
    leftWall->setColor(glm::vec3(0.0)); // Black
    rightWall->setColor(glm::vec3(0.0)); // Black
    backWall->setColor(glm::vec3(0.1)); // Darker Gray
    cube->setColor(glm::vec3(1.0, 0.0, 0.0));
    items.push_back(topWall);
    items.push_back(bottomWall);
    items.push_back(leftWall);
    items.push_back(rightWall);
    items.push_back(backWall);
    items.push_back(cube);
}

void OpenGLView::paintGL() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(qDegreesToRadians(45.0) , 16.0 / 9.0, 1.0, 10.0);
//    glm::mat4 view = glm::lookAt(glm::vec3(0.5 + 5 * sin(qDegreesToRadians(eTimer.elapsed()) / 30), 0.5 + 5 * cos(qDegreesToRadians(eTimer.elapsed()) / 30), 1.5),
    glm::mat4 view = glm::lookAt(glm::vec3(0.5, -1.0, 0.5),
                                 glm::vec3(0.5, 0.5, 0.5),
                                 glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 lightPos(20.0, 20.0, -10);
    glm::vec3 cameraPos(0.0);
    for(auto &i: items) {
        shader.drawElements(i->va, i->vb, i->eb, i->color, projection, view, model, lightPos, cameraPos);
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
