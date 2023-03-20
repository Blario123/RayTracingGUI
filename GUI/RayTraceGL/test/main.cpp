#include <QApplication>
#include <QGridLayout>
#include "../openGlView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto *view = new OpenGLView;
    view->show();

    return a.exec();
}
