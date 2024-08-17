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
    QSurfaceFormat::setDefaultFormat(format);

    QGridLayout* layout = new QGridLayout;
    QSlider* xSlider = new QSlider(Qt::Orientation::Horizontal);
    xSlider->setRange(0, 3600);
    QSlider* ySlider = new QSlider(Qt::Orientation::Horizontal);
    ySlider->setRange(0, 3600);
    QSlider* zSlider = new QSlider(Qt::Orientation::Horizontal);
    zSlider->setRange(0, 3600);
    QLineEdit* xL = new QLineEdit;
    QLineEdit* yL = new QLineEdit;
    QLineEdit* zL = new QLineEdit;

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

    QWidget* m = new QWidget;
    m->setLayout(layout);
    m->show();
    QWidget::connect(xSlider, &QSlider::sliderMoved, view, &OpenGLView::setXAngle);
    QWidget::connect(xSlider, &QSlider::sliderMoved, xL, [xL, xSlider](){
        xL->setText(QString::number(xSlider->sliderPosition()/10.0f));
    });
    QWidget::connect(ySlider, &QSlider::sliderMoved, view, &OpenGLView::setYAngle);
    QWidget::connect(ySlider, &QSlider::sliderMoved, yL, [yL, ySlider](){
        yL->setText(QString::number(ySlider->sliderPosition()/10.0f));
    });
    QWidget::connect(zSlider, &QSlider::sliderMoved, view, &OpenGLView::setZAngle);
    QWidget::connect(zSlider, &QSlider::sliderMoved, zL, [zL, zSlider](){
        zL->setText(QString::number(zSlider->sliderPosition()/10.0f));
    });

    return a.exec();
}
