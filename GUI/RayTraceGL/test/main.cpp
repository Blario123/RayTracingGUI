#include <QApplication>
#include <QGridLayout>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include "../openGlView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(10);
    QSurfaceFormat::setDefaultFormat(format);

    auto* layout = new QGridLayout;
    auto* xSlider = new QSlider(Qt::Orientation::Horizontal);
    xSlider->setRange(0, 3600);
    auto* ySlider = new QSlider(Qt::Orientation::Horizontal);
    ySlider->setRange(0, 3600);
    auto* zSlider = new QSlider(Qt::Orientation::Horizontal);
    zSlider->setRange(0, 3600);
    auto* xL = new QLineEdit;
    auto* yL = new QLineEdit;
    auto* zL = new QLineEdit;

    auto *view = new OpenGLView;
    layout->addWidget(view, 0, 0, 1, 3);
    layout->addWidget(new QLabel("X:"), 1, 0);
    layout->addWidget(xSlider, 1, 1);
    layout->addWidget(xL, 1, 2);
    layout->addWidget(new QLabel("Y:"), 2, 0);
    layout->addWidget(ySlider, 2, 1);
    layout->addWidget(yL, 2, 2);
    layout->addWidget(new QLabel("Z:"), 3, 0);
    layout->addWidget(zSlider, 3, 1);
    layout->addWidget(zL, 3, 2);

    auto* m = new QWidget;
    m->setLayout(layout);
    m->show();
    QMetaObject::Connection c;
    c = QWidget::connect(xSlider, &QSlider::sliderMoved, view, &OpenGLView::setXAngle);
    c = QWidget::connect(xSlider, &QSlider::sliderMoved, xL, [xL, xSlider](){
        xL->setText(QString::number((float) xSlider->sliderPosition()/10.0f));
    });
    c = QWidget::connect(ySlider, &QSlider::sliderMoved, view, &OpenGLView::setYAngle);
    c = QWidget::connect(ySlider, &QSlider::sliderMoved, yL, [yL, ySlider](){
        yL->setText(QString::number((float) ySlider->sliderPosition()/10.0f));
    });
    c = QWidget::connect(zSlider, &QSlider::sliderMoved, view, &OpenGLView::setZAngle);
    c = QWidget::connect(zSlider, &QSlider::sliderMoved, zL, [zL, zSlider](){
        zL->setText(QString::number((float) zSlider->sliderPosition()/10.0f));
    });

    return QApplication::exec();
}
