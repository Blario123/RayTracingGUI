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

    mDimensions = {1.0, 1.0, 1.0};
    setFov(33.0);

    createScene();

    QSharedPointer<OpenGLItem> cube(new OpenGLItemCuboid(glm::vec3(0.1, 0.1, 0.0),
                                                         glm::vec3(0.2)));
    cube->setColor(glm::vec3(1.0, 0.0, 0.0));
    items.push_back(cube);
}

void OpenGLView::paintGL() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = glm::perspective(mFov , 16.0 / 9.0, 1.0, 100.0);
    // glm::mat4 view = glm::lookAt(glm::vec3(0.5 + 5 * sin(qDegreesToRadians(eTimer.elapsed()) / 30), 0.5 + 5 * cos(qDegreesToRadians(eTimer.elapsed()) / 30), 1.5),
    double greaterDim = mDimensions.z > mDimensions.x ? mDimensions.z : mDimensions.x;
    glm::mat4 view = glm::lookAt(glm::vec3(mDimensions.x / 2.0, -((greaterDim/2)/tan(mFov/2)), mDimensions.z / 2.0),
                                 glm::vec3(mDimensions.x / 2.0, 0.0, mDimensions.z / 2.0),
                                 glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 lightPos(20.0, 20.0, -10);
    glm::vec3 cameraPos(0.0);

    for(auto &i: scene) {
        shader.drawElements(i->va, i->vb, i->eb, i->color, projection, view, model, lightPos, cameraPos);
    }
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
    setDimensions(glm::vec3(event->text().toFloat()));
//     setDimensions({event->text().toFloat(), 1.0, 1.0});
    QOpenGLWidget::keyPressEvent(event);
}

void OpenGLView::setDimensions(const glm::vec3 &d) {
    mDimensions = d;
    updateScene();
}

void OpenGLView::setFov(double fov) {
    mFov = qDegreesToRadians(fov);
}

void OpenGLView::createScene() {
    QSharedPointer<OpenGLItem> topWall(new OpenGLItemCuboid(    glm::vec3(0.0, 0.0, mDimensions.z),
                                                                glm::vec3(mDimensions.x, mDimensions.y, 0.0)));
    QSharedPointer<OpenGLItem> bottomWall(new OpenGLItemCuboid( glm::vec3(0.0, 0.0, 0.0),
                                                                glm::vec3(mDimensions.x, mDimensions.y, 0.0)));
    QSharedPointer<OpenGLItem> leftWall(new OpenGLItemCuboid(   glm::vec3(0.0, 0.0, 0.0),
                                                                glm::vec3(0.0, mDimensions.y, mDimensions.z)));
    QSharedPointer<OpenGLItem> rightWall(new OpenGLItemCuboid(  glm::vec3(mDimensions.x, 0.0, 0.0),
                                                                glm::vec3(0.0, mDimensions.y, mDimensions.z)));
    QSharedPointer<OpenGLItem> backWall(new OpenGLItemCuboid(   glm::vec3(0.0, mDimensions.y, 0.0),
                                                                glm::vec3(mDimensions.x, 0.0, mDimensions.z)));
    topWall->setColor(glm::vec3(1.0)); // White
    bottomWall->setColor(glm::vec3(0.2)); // Dark Gray
    leftWall->setColor(glm::vec3(0.0)); // Black
    rightWall->setColor(glm::vec3(0.0)); // Black
    backWall->setColor(glm::vec3(0.1)); // Darker Gray
    scene.push_back(topWall);
    scene.push_back(bottomWall);
    scene.push_back(leftWall);
    scene.push_back(rightWall);
    scene.push_back(backWall);
}

void OpenGLView::updateScene() {
    scene[0].dynamicCast<OpenGLItemCuboid>()->setDimensions(glm::vec3(mDimensions.x, mDimensions.y, 0.0));
    scene[0].dynamicCast<OpenGLItemCuboid>()->setPosition(glm::vec3(0.0, 0.0, mDimensions.z));
    scene[1].dynamicCast<OpenGLItemCuboid>()->setDimensions(glm::vec3(mDimensions.x, mDimensions.y, 0.0));
    scene[2].dynamicCast<OpenGLItemCuboid>()->setDimensions(glm::vec3(0.0, mDimensions.y, mDimensions.z));
    scene[3].dynamicCast<OpenGLItemCuboid>()->setDimensions(glm::vec3(0.0, mDimensions.y, mDimensions.z));
    scene[3].dynamicCast<OpenGLItemCuboid>()->setPosition(glm::vec3(mDimensions.x, 0.0, 0.0));
    scene[4].dynamicCast<OpenGLItemCuboid>()->setDimensions(glm::vec3(mDimensions.x, 0.0, mDimensions.z));
    scene[4].dynamicCast<OpenGLItemCuboid>()->setPosition(glm::vec3(0.0, mDimensions.y, 0.0));
}
