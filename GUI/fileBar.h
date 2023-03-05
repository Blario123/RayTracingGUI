#ifndef FILEBAR_H
#define FILEBAR_H

#include <QMenuBar>

class FileBar : public QMenuBar {
    Q_OBJECT
public:
    explicit FileBar(QWidget *parent = nullptr);
    ~FileBar() override = default;
    QAction *closeAction;
    QAction *saveAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
private:
    QMenu *fileMenu;
    QMenu *aboutMenu;
public slots:
    void save();
signals:
};

#endif //FILEBAR_H
