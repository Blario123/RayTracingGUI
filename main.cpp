#include <QApplication>
#include <QStyleFactory>

#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QApplication a(argc, argv);
    GUI g;
    g.show();
    return QApplication::exec();
}
